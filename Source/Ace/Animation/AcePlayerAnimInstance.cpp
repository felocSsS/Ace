// Ace Game. All Rights Reserved.

#include "Animation/AcePlayerAnimInstance.h"
#include "Components/SkinnedMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/AceWeaponComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/AcePlayerCharacter.h"
#include "Weapon/AceBaseWeapon.h"
#include "Curves/CurveVector.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/AceCharacterMovementComponent.h"

void UAcePlayerAnimInstance::NativeBeginPlay()
{
    Super::NativeBeginPlay();
    
    Character = Cast<AAcePlayerCharacter>(TryGetPawnOwner());
    if (!Character) return;

    PlayerController = Character->GetController<APlayerController>();
    if (!PlayerController) return;

    MovementComponent = Cast<UAceCharacterMovementComponent>(Character->GetMovementComponent());
    if (!MovementComponent) return;
    
    WeaponComponent = Cast<UAceWeaponComponent>(Character->GetComponentByClass(UAceWeaponComponent::StaticClass()));
    if (!WeaponComponent) return;

    WeaponComponent->CurrentWeaponChangedDelegate.AddDynamic(this, &UAcePlayerAnimInstance::WeaponChanged);
    WeaponComponent->UpdateWeaponInfoDelegate.AddDynamic(this, &UAcePlayerAnimInstance::UpdateInfo);
    OldTurnRotation = Character->GetControlRotation();
    
    if (MoveInSidesCurve)
    {
        UpdateForModeInSides.BindUFunction(this, "TimeLineForWalkUpdate");
        TimeLineForModeInSides.AddInterpVector(MoveInSidesCurve, UpdateForModeInSides);
    }

    if (JumpStartCurve && JumpEndCurve)
    {
        UpdateForJump.BindUFunction(this, "TimeLineForJumpUpdate");
        TimeLineForJump.AddInterpVector(JumpStartCurve, UpdateForJump, NAME_None, "Track1");   
    }

    UpdateForRecoil.BindUFunction(this, "TimeLineForRecoilUpdate");
    TimelineForRecoil.AddInterpVector(nullptr, UpdateForRecoil, NAME_None, "Track1");

    if (RunVectorCurve && RunRotatorCurve)
    {
        UpdateForRun1.BindUFunction(this, "TimeLineForRunUpdate");
        TimelineForRun.AddInterpVector(RunVectorCurve, UpdateForRun1);
        TimelineForRun.AddInterpVector(RunRotatorCurve, UpdateForRun2);
        TimelineForRun.SetTimelineLength(1000000.0f);
    }
}

void UAcePlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    
    SetCharacterVars();
    SetAimOffset();
    SetRelativeCameraTransform();
    SetADSAlpha(DeltaSeconds);
    SetCanEffect(DeltaSeconds);
    SetCanRunning(DeltaSeconds);
    SetRunTransform(DeltaSeconds);
    SetWalkWeaponSway(DeltaSeconds);
    SetMoveInSides(DeltaSeconds);
    SetTurnWeaponSway(DeltaSeconds);
    SetJumpShake(DeltaSeconds);
    InterpRecoil(DeltaSeconds);
    InterpFinalRecoil(DeltaSeconds);

    TimeLineForModeInSides.TickTimeline(DeltaSeconds);
    TimeLineForJump.TickTimeline(DeltaSeconds);
    TimelineForRecoil.TickTimeline(DeltaSeconds);
    TimelineForRun.TickTimeline(DeltaSeconds);
    
    if (bIsMovingRight || bIsMovingForward)
        TimeLineForModeInSides.Play();
    else
    {
        TimeLineForModeInSides.Reverse();
        TimeLineForModeInSides.SetNewTime(0.0f);
    }
}

#pragma region TimelineCode

void UAcePlayerAnimInstance::TimeLineForWalkUpdate(const FVector MoveVector)
{
    FVector Translation = FVector::ZeroVector;
    FRotator Rotation = FRotator::ZeroRotator;
    
    if (bIsMovingRight)
    {
        Translation.Y = MoveVector.X * -MoveRightValue;
        Translation.Y *= ShakingModifier;
        Rotation.Roll = MoveVector.Y * MoveRightValue;
        Rotation.Roll *= ShakingModifier;
    }
    else
    {
        Translation.Y = 0.0f;
        Rotation.Roll = 0.0f;
    }

    if (bIsMovingForward)
    {
        Translation.X = MoveVector.X * -MoveForwardValue;
        Translation.X *= ShakingModifier;
    }
    else
    {
        Translation.X = 0.0f;
    }
    
    MoveInSidesSway.SetTranslation(Translation);
    MoveInSidesSway.SetRotation(Rotation.Quaternion());
}

void UAcePlayerAnimInstance::SetMoveInSides(float DeltaSeconds)
{
    SidesWeaponSway = UKismetMathLibrary::TInterpTo(SidesWeaponSway, MoveInSidesSway, DeltaSeconds, 5.0f);
}

void UAcePlayerAnimInstance::TimeLineForJumpUpdate(const FVector JumpVector)
{
    JumpPosition = JumpVector.Z;
}

void UAcePlayerAnimInstance::SetJumpShake(float DeltaSeconds)
{
    ZPositionJumpTransform = UKismetMathLibrary::FInterpTo(ZPositionJumpTransform, JumpPosition, DeltaSeconds, 20.0f);
    JumpTransform.SetTranslation(FVector(0.0f, 0.0f, ZPositionJumpTransform));
}

void UAcePlayerAnimInstance::TimeLineForRecoilUpdate(const FVector RecoilVector)
{
    if (!PlayerController) return;
    
    PlayerController->AddPitchInput(-RecoilVector.Y);
    PlayerController->AddYawInput(RecoilVector.X);
}

void UAcePlayerAnimInstance::TimeLineForRunUpdate()
{
    RunUpdate(RunVectorCurve->GetVectorValue(TimelineForRun.GetPlaybackPosition()),
        RunRotatorCurve->GetVectorValue(TimelineForRun.GetPlaybackPosition()));
}

void UAcePlayerAnimInstance::RunUpdate(const FVector RunVector, const FVector RunRotator)
{
    const FQuat Rotation = FRotator(RunRotator.Y, RunRotator.Z, RunRotator.X).Quaternion();
    IntermediateRunTransform.SetLocation(RunVector);
    IntermediateRunTransform.SetRotation(Rotation);
}

void UAcePlayerAnimInstance::SetRunTransform(float DeltaSeconds)
{
    RunTransform = UKismetMathLibrary::TInterpTo(RunTransform, IntermediateRunTransform, DeltaSeconds, 10.0f);
}

#pragma endregion TimelineCode

void UAcePlayerAnimInstance::SetCharacterVars()
{
    if (!Character || !Character->GetController()) return;

    CharacterVelocity = Character->GetVelocity().Length();
    Direction = Character->GetMovementDirection();
    ActualRotation = Character->GetController()->K2_GetActorRotation();
}

void UAcePlayerAnimInstance::SetAimOffset()
{
    AimOffsetRotation = FRotator(0.0f,
        0.0f,
        (UKismetMathLibrary::SelectFloat(ActualRotation.Pitch - 360,
                  ActualRotation.Pitch * -1.0f,
            ActualRotation.Pitch > 180) / 3 ));
}

void UAcePlayerAnimInstance::SetADSAlpha(float DeltaSeconds)
{
    if (!Character) return;
    
    CanAim = FMath::FInterpTo(CanAim, Character->ADSAlpha, DeltaSeconds, 10.0f); //TODO interpSpeed сделать как переменную
}

void UAcePlayerAnimInstance::SetCanEffect(float DeltaSeconds)
{
    CanEffect = UKismetMathLibrary::FInterpTo(CanEffect, IntermediateCanEffect, DeltaSeconds, 10.0f);
}

void UAcePlayerAnimInstance::SetCanRunning(float DeltaSeconds)
{
    CanRunning = UKismetMathLibrary::FInterpTo(CanRunning, IntermediateCanRunning, DeltaSeconds, 10.0f);
}

void UAcePlayerAnimInstance::SetWalkWeaponSway(float DeltaSeconds)
{
    if (!WalkCurve || !Character || !Character->GetMovementComponent()) return;

    FVector VelocityVector = MovementComponent->Velocity;
    VelocityVector.Z = 0.0f;
    
    const float MaxSpeed = MovementComponent->GetMaxSpeed();
    float Velocity = VelocityVector.Size();
    Velocity = UKismetMathLibrary::NormalizeToRange(Velocity, (MaxSpeed / 0.9f * -1.0f), MaxSpeed); // TODO 0,9f превратить в переменную
    
    const FVector CurveValue =  WalkCurve->GetVectorValue(Character->GetGameTimeSinceCreation());
    WalkSwayLocation = UKismetMathLibrary::VInterpTo(WalkSwayLocation, CurveValue, DeltaSeconds, 10.0f);
    WalkSwayLocation = WalkSwayLocation * FMath::Clamp(Velocity, 0.0f, 1.0f);
}

void UAcePlayerAnimInstance::SetTurnWeaponSway(float DeltaSeconds)
{
    if (!Character) return;
    
    const FRotator CurrentRotation = Character->GetControlRotation();
    
    TurnRotation = UKismetMathLibrary::RInterpTo(TurnRotation, CurrentRotation - OldTurnRotation, DeltaSeconds, 3.0f);
    TurnRotation.Yaw = FMath::Clamp(TurnRotation.Yaw, -2.0f, 2.0f);
    TurnRotation.Roll = FMath::Clamp(TurnRotation.Roll,-2.0f, 2.0f);
    
    FinalTurnRotation = FRotator(0.0f,
                                FMath::Clamp(TurnRotation.Yaw, -2.0f, 2.0f),
                                FMath::Clamp(TurnRotation.Pitch * -1.0f,-2.0f, 2.0f));

    OldTurnRotation = CurrentRotation;
}

void UAcePlayerAnimInstance::SetRelativeCameraTransform()
{
    if(!Character || !Character->GetController() || !Character->CameraComponent || !Character->GetMesh()) return;
    
    const auto CameraTransform = FTransform(Character->GetController()->K2_GetActorRotation(), Character->CameraComponent->GetComponentLocation());
    
    const FTransform RootOffset = Character->GetMesh()->GetSocketTransform("root", RTS_Component).Inverse() *
        Character->GetMesh()->GetSocketTransform("ik_hand_root");
    
    RelativeCameraTransform = CameraTransform.GetRelativeTransform(RootOffset);
}

void UAcePlayerAnimInstance::WeaponChanged(AAceBaseWeapon* NewWeapon)
{
    CurrentWeapon = NewWeapon;
    TimelineForRecoil.SetVectorCurve(CurrentWeapon->GetRecoilCurve(), "Track1");
    GetRelativeRightHandTransform();
    GetLeftHandTransform();
}

void UAcePlayerAnimInstance::UpdateInfo()
{
    GetRelativeRightHandTransform();
    GetLeftHandTransform();
}

void UAcePlayerAnimInstance::GetLeftHandTransform()
{
    if (!CurrentWeapon || !CurrentWeapon->WeaponMesh || !Character || !Character->GetMesh()) return;
    
    const FTransform SocketTransform = CurrentWeapon->GetGripTransform();
    FVector OutPosition;
    FRotator OutRotation;
    Character->GetMesh()->TransformToBoneSpace("hand_r", SocketTransform.GetLocation(), SocketTransform.Rotator(), OutPosition, OutRotation);
    LeftHandTransform.SetLocation(OutPosition);
    LeftHandTransform.SetRotation(OutRotation.Quaternion());
}

void UAcePlayerAnimInstance::GetRelativeRightHandTransform()
{
    if (!CurrentWeapon || !CurrentWeapon->WeaponMesh || !Character || !Character->GetMesh()) return;
    
    const auto AimSocketTransform = CurrentWeapon->GetSightTransform();
    const auto RightHandTransform = GetSocketTransform(Character->GetMesh(), "hand_r");
    RelativeHandTransform = UKismetMathLibrary::MakeRelativeTransform(AimSocketTransform, RightHandTransform);
}

void UAcePlayerAnimInstance::Fire()
{
    FVector RecoilLoc = FinalRecoilTransform.GetLocation();
    RecoilLoc.X += FMath::RandRange(8.0f, 13.0f);
    FinalRecoilTransform.SetLocation(-RecoilLoc); 
}

void UAcePlayerAnimInstance::StartJump()
{
    ResetJumpTimeline();
    TimeLineForJump.Play();
    IntermediateCanEffect = 0.0f;
    IntermediateCanRunning = 0.0f;
}

void UAcePlayerAnimInstance::FinishJump()
{
    TimeLineForJump.SetVectorCurve(JumpEndCurve, "Track1");
    TimeLineForJump.SetNewTime(0.0f);
    TimeLineForJump.Play();
    IntermediateCanEffect = 1.0f;
    IntermediateCanRunning = 1.0f;
}

void UAcePlayerAnimInstance::StartShooting()
{
    TimelineForRecoil.Play();
}

void UAcePlayerAnimInstance::EndShooting()
{
    TimelineForRecoil.Stop();
    TimelineForRecoil.SetNewTime(0.0f);
}

void UAcePlayerAnimInstance::StartRunning()
{
    TimelineForRun.Play();
    IntermediateCanEffect = 0.0f;
}

void UAcePlayerAnimInstance::StopRunning()
{
    TimelineForRun.Stop();
    TimelineForRun.SetNewTime(0.0f);
    IntermediateRunTransform.SetLocation(FVector::ZeroVector);
    IntermediateRunTransform.SetRotation(FRotator::ZeroRotator.Quaternion());
    IntermediateCanEffect = 1.0f;
}

void UAcePlayerAnimInstance::ResetJumpTimeline()
{
    TimeLineForJump.SetVectorCurve(JumpStartCurve, "Track1");
    TimeLineForJump.Stop();
    TimeLineForJump.SetNewTime(0.0f);
}

void UAcePlayerAnimInstance::InterpFinalRecoil(float DeltaSeconds)
{
    FinalRecoilTransform = UKismetMathLibrary::TInterpTo(FinalRecoilTransform, FTransform(), DeltaSeconds, 10.0f);
}

void UAcePlayerAnimInstance::InterpRecoil(float DeltaSeconds)
{
    RecoilTransform = UKismetMathLibrary::TInterpTo(RecoilTransform, FinalRecoilTransform, DeltaSeconds, 10.0f);
}

FTransform UAcePlayerAnimInstance::GetSocketTransform(USceneComponent* Object, FName Socket) const
{
    if (!Object) return FTransform();

    return Object->GetSocketTransform(Socket);
}