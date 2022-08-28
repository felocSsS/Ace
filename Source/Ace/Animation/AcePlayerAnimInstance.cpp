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

void UAcePlayerAnimInstance::NativeBeginPlay()
{
    Super::NativeBeginPlay();
    
    Character = Cast<AAcePlayerCharacter>(TryGetPawnOwner());
    if (!Character) return;

    PlayerController = Character->GetController<APlayerController>();
    if (!PlayerController) return;

    WeaponComponent = Cast<UAceWeaponComponent>(Character->GetComponentByClass(UAceWeaponComponent::StaticClass()));
    if (!WeaponComponent) return;

    WeaponComponent->CurrentWeaponChangedDelegate.AddDynamic(this, &UAcePlayerAnimInstance::WeaponChanged);
    OldTurnRotation = Character->GetControlRotation();
    
    if (!MoveInSidesCurve) return;
    
	FOnTimelineVector Update;
    Update.BindUFunction(this, "TimelineUpdate");
    TimeLine.AddInterpVector(MoveInSidesCurve, Update);
}

void UAcePlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    
    SetCharacterVars();
    SetAimOffset();
    SetRelativeCameraTransform();
    SetADSAlpha(DeltaSeconds);
    SetWalkWeaponSway(DeltaSeconds);
    SetMoveInSides(DeltaSeconds);
    SetTurnWeaponSway(DeltaSeconds);
    GetLeftHandTransform();
    TimeLine.TickTimeline(DeltaSeconds);

    InterpRecoil(DeltaSeconds);
    InterpFinalRecoil(DeltaSeconds);

    if (bIsMovingRight || bIsMovingForward)
        TimeLine.Play();
    else
    {    
        TimeLine.Reverse();
        TimeLine.SetNewTime(0.0f);
    }
}

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
    
    ADSAlpha = FMath::FInterpTo(ADSAlpha, Character->ADSAlpha, DeltaSeconds, 15.0f); //TODO interpSpeed сделать как переменную
}

void UAcePlayerAnimInstance::SetWalkWeaponSway(float DeltaSeconds)
{
    if (!WalkCurve || !Character || !Character->GetMovementComponent()) return;

    FVector VelocityVector = Character->GetMovementComponent()->Velocity;
    VelocityVector.Z = 0.0f;
    
    const float MaxSpeed = Character->GetMovementComponent()->GetMaxSpeed();
    float Velocity = VelocityVector.Size();
    Velocity = UKismetMathLibrary::NormalizeToRange(Velocity, (MaxSpeed / 0.9f * -1.0f), MaxSpeed); // TODO 0,9f превратить в переменную
    
    const FVector CurveValue =  WalkCurve->GetVectorValue(Character->GetGameTimeSinceCreation());
    WalkSwayLocation = UKismetMathLibrary::VInterpTo(WalkSwayLocation, CurveValue, DeltaSeconds, 10.0f);
    WalkSwayLocation *= Velocity;
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

void UAcePlayerAnimInstance::SetMoveInSides(float DeltaSeconds)
{
    SidesWeaponSway = UKismetMathLibrary::TInterpTo(SidesWeaponSway, MoveInSidesSway, DeltaSeconds, 5.0f);
}

void UAcePlayerAnimInstance::TimelineUpdate(FVector MoveVector)
{
    FVector Translation = FVector();
    FRotator Rotation = FRotator();
    
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
    
    Translation.Z = 0.0f;
    Rotation.Pitch = 0.0f;
    
    MoveInSidesSway.SetTranslation(Translation);
    MoveInSidesSway.SetRotation(Rotation.Quaternion());
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
    GetRelativeRightHandTransform();
}

void UAcePlayerAnimInstance::GetLeftHandTransform()
{
    if (!CurrentWeapon || !CurrentWeapon->WeaponMesh || !Character || !Character->GetMesh()) return;
    
    const FTransform SocketTransform = CurrentWeapon->GetGripTransform();/*GetSocketTransform(CurrentWeapon->WeaponMesh, "l_hand_socket");*/
    FVector OutPosition;
    FRotator OutRotation;
    Character->GetMesh()->TransformToBoneSpace("hand_r", SocketTransform.GetLocation(), SocketTransform.Rotator(), OutPosition, OutRotation);
    LeftHandTransform.SetLocation(OutPosition);
    LeftHandTransform.SetRotation(OutRotation.Quaternion());
}

void UAcePlayerAnimInstance::GetRelativeRightHandTransform()
{
    if (!CurrentWeapon || !CurrentWeapon->WeaponMesh || !Character || !Character->GetMesh()) return;
    
    const auto AimSocketTransform = CurrentWeapon->GetSightTransform();/*GetSocketTransform(CurrentWeapon->WeaponMesh, "Aim");*/
    const auto RightHandTransform = GetSocketTransform(Character->GetMesh(), "hand_r");
    RelativeHandTransform = UKismetMathLibrary::MakeRelativeTransform(AimSocketTransform, RightHandTransform);
}

void UAcePlayerAnimInstance::Fire()
{
    FVector RecoilLoc = FinalRecoilTransform.GetLocation();
    RecoilLoc.X += FMath::RandRange(5.0f, 7.0f);
    FinalRecoilTransform.SetLocation(-RecoilLoc); 
}

void UAcePlayerAnimInstance::InterpFinalRecoil(float DeltaSeconds)
{
    FinalRecoilTransform = UKismetMathLibrary::TInterpTo(FinalRecoilTransform, FTransform(), DeltaSeconds, 10.0f);
}

void UAcePlayerAnimInstance::InterpRecoil(float DeltaSeconds)
{
    RecoilTransform = UKismetMathLibrary::TInterpTo(RecoilTransform, FinalRecoilTransform, DeltaSeconds, 10.0f);
}

FTransform UAcePlayerAnimInstance::GetSocketTransform(USceneComponent* Object, FName Socket)
{
    if (!Object) return FTransform();

    return Object->GetSocketTransform(Socket);
}