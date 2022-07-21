// Ace Game. All Rights Reserved.


#include "Animation/AcePlayerAnimInstance.h"
#include "Components/SkinnedMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/AceWeaponComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/AcePlayerCharacter.h"
#include "Weapon/AceBaseWeapon.h"

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
}

void UAcePlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    SetAimOffset();
    SetCharacterVars();
    SetADSAlpha(DeltaSeconds);
    SetRelativeCameraTransform();
}

void UAcePlayerAnimInstance::SetAimOffset()
{
    AimOffsetRotation = FRotator(0.0f,
        0.0f,
        (UKismetMathLibrary::SelectFloat(ActualRotation.Pitch - 360,
                  ActualRotation.Pitch * -1.0f,
            ActualRotation.Pitch > 180) / 5 ));
}

void UAcePlayerAnimInstance::SetCharacterVars()
{
    if (!Character || !Character->GetController()) return;

    Velocity = Character->GetVelocity().Length();
    Direction = Character->GetMovementDirection();
    ActualRotation = Character->GetController()->K2_GetActorRotation();
}

void UAcePlayerAnimInstance::SetADSAlpha(float DeltaSeconds)
{
    if (!Character) return;
    
    ADSAlpha = FMath::FInterpTo(ADSAlpha, Character->ADSAlpha, DeltaSeconds, 15.0f); //TODO interpSpeed сделать как переменную
}

void UAcePlayerAnimInstance::SetRelativeCameraTransform()
{
    if(!Character || !Character->GetController()) return;
    
    CameraTransform = FTransform(Character->GetController()->K2_GetActorRotation(), Character->CameraComponent->GetComponentLocation());

    const FTransform& RootOffset = Character->GetMesh()->GetSocketTransform("root", RTS_Component).Inverse() *
        Character->GetMesh()->GetSocketTransform("ik_hand_root");
    RelativeCameraTransform = CameraTransform.GetRelativeTransform(RootOffset);
}

void UAcePlayerAnimInstance::WeaponChanged(AAceBaseWeapon* NewWeapon)
{
    CurrentWeapon = NewWeapon;
    SetIKTransforms();
}

void UAcePlayerAnimInstance::SetIKTransforms()
{
    if (!CurrentWeapon || !CurrentWeapon->WeaponMesh || !Character || !Character->GetMesh()) return;
    
    RHandToSightsTransform = CurrentWeapon->WeaponMesh->GetSocketTransform("Aim").GetRelativeTransform(Character->GetMesh()->GetSocketTransform("hand_r"));
}

FTransform UAcePlayerAnimInstance::GetSocketTransform(USceneComponent* Object, FName Socket)
{
    if (!Object) return FTransform();

    return Object->GetSocketTransform(Socket);
}
