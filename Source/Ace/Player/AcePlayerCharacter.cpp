// Ace Game. All Rights Reserved.


#include "Player/AcePlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Animation/AcePlayerAnimInstance.h"
#include "Components/AceWeaponComponent.h"

AAcePlayerCharacter::AAcePlayerCharacter()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(GetMesh(), "head");
    CameraComponent->bUsePawnControlRotation = true;

    GetMesh()->bVisibleInReflectionCaptures= true;
    GetMesh()->bCastHiddenShadow = true;
    
    ClientMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ClientMesh"));
    ClientMesh->SetCastShadow(false);
    ClientMesh->bCastHiddenShadow = false;
    ClientMesh->bVisibleInReflectionCaptures = false;
    ClientMesh->SetTickGroup(ETickingGroup::TG_PostPhysics);
    ClientMesh->SetupAttachment(GetMesh());
}

void AAcePlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    AnimInstance = Cast<UAcePlayerAnimInstance>(GetMesh()->GetAnimInstance());
    ADSAlpha = 0.0f;
    ClientMesh->HideBoneByName("neck_01", PBO_None);
    GetMesh()->SetVisibility(false);
}

void AAcePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAcePlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAcePlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AAcePlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &AAcePlayerCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UAceWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UAceWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AAcePlayerCharacter::Aim);
    PlayerInputComponent->BindAction("Aim", IE_Released, this, &AAcePlayerCharacter::ResetAim);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UAceWeaponComponent::NextWeapon);
}

void AAcePlayerCharacter::MoveForward(float Value)
{
	if (Value == 0.0f) return;

	AddMovementInput(GetActorForwardVector(), Value);
}

void AAcePlayerCharacter::MoveRight(float Value)
{
	if (Value == 0.0f) return;

	AddMovementInput(GetActorRightVector(), Value);
}

void AAcePlayerCharacter::Aim()
{
    ADSAlpha = 1.0f;
}

void AAcePlayerCharacter::ResetAim()
{
    ADSAlpha = 0.0f;
}


