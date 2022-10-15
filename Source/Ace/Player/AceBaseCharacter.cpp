// Ace Game. All Rights Reserved.


#include "Player/AceBaseCharacter.h"
#include "Components/AceWeaponComponent.h"
#include "Components/AceHealthComponent.h"
#include "Components/AceCharacterMovementComponent.h"

AAceBaseCharacter::AAceBaseCharacter(const  FObjectInitializer& ObjInit) :
    Super(ObjInit.SetDefaultSubobjectClass<UAceCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

    HealthComponent = CreateDefaultSubobject<UAceHealthComponent>("Health Component");

    WeaponComponent = CreateDefaultSubobject<UAceWeaponComponent>("Weapon Component");
}

void AAceBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

    LandedDelegate.AddDynamic(this, &AAceBaseCharacter::OnGroundLanded);
}

void AAceBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
    
}

float AAceBaseCharacter::GetCharacterVelocity() const
{
    return GetVelocity().Length();
}

float AAceBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero()) return 0.0f;

    const FVector VelocityNormal = GetVelocity().GetSafeNormal();
    const float AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const FVector CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const float Degrees = FMath::RadiansToDegrees(AngleBetween);

    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}



