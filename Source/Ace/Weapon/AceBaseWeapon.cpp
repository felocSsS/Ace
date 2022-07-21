// Ace Game. All Rights Reserved.


#include "Weapon/AceBaseWeapon.h"

AAceBaseWeapon::AAceBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    WeaponMesh->SetupAttachment(RootComponent);
}

void AAceBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
}

void AAceBaseWeapon::StartFire()
{
}

void AAceBaseWeapon::StopFire()
{
}

void AAceBaseWeapon::MakeShot()
{
}

void AAceBaseWeapon::AddRecoil()
{
}




