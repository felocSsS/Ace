// Ace Game. All Rights Reserved.


#include "Components/AceWeaponComponent.h"

#include "AceInventoryComponent.h"
#include "GameFramework/Character.h"
#include "Player/AcePlayerCharacter.h"
#include "Weapon/AceBaseWeapon.h"

UAceWeaponComponent::UAceWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAceWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

    Weapons.SetNum(5);
    
    CurrentWeaponIndex = 0;
    SpawnStartWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void UAceWeaponComponent::SpawnStartWeapons()
{
    AAcePlayerCharacter* Character = Cast<AAcePlayerCharacter>(GetOwner());
    if(!Character || !GetWorld()) return;

    for (auto Weapon : StartWeapons)
    {
        auto SpawnedWeapon = GetWorld()->SpawnActor<AAceBaseWeapon>(Weapon.WeaponClass);
        if(!SpawnedWeapon) return;
        
        SpawnedWeapon->SetOwner(Character);
        Character->InventoryComponent->AddItem(SpawnedWeapon->GetItemObject());
        SpawnedWeapon->SpawnStartAttachment();
        Weapons.Add(SpawnedWeapon);

        AttachWeaponToSocket(SpawnedWeapon, Character->GetMesh(), "InventorySlotSocket");
    }
}

void UAceWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    if (WeaponIndex < 0 || !Weapons.IsValidIndex(WeaponIndex)) return;

    const ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    if (CurrentWeapon)
    {
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), "InventorySlotSocket");
    }
    const AAceBaseWeapon* OldWeapon = CurrentWeapon;
    CurrentWeapon = Weapons[WeaponIndex];
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), "RightHandSocket");
    CurrentWeaponChangedDelegate.Broadcast(CurrentWeapon);
}

void UAceWeaponComponent::AddWeapon(AAceBaseWeapon* Item, int32 AtIndex)
{
    if (!Item) return;

    Weapons[AtIndex] = Item;
}

void UAceWeaponComponent::AttachWeaponToSocket(AAceBaseWeapon* Weapon, USceneComponent* SceneComponent,
                                               const FName SocketName)
{
    if(!Weapon || !SceneComponent) return;

    const FAttachmentTransformRules AttachmentsRoles(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentsRoles, SocketName);
}

void UAceWeaponComponent::StartFire()
{
    if (!CanFire() || !CurrentWeapon) return;

    CurrentWeapon->StartFire();
}

void UAceWeaponComponent::StopFire()
{
    if (!CanFire() || !CurrentWeapon) return;

    CurrentWeapon->StopFire();
}

void UAceWeaponComponent::Reload()
{
    ChangeClip();
}

void UAceWeaponComponent::ChangeClip()
{
    if (!CanReload()) return;
    
    CurrentWeapon->StopFire();
    CurrentWeapon->ChangeClip();
}

void UAceWeaponComponent::NextWeapon()
{
    if (!CanEquip()) return;

    CurrentWeaponIndex = (CurrentWeaponIndex + 1 ) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

bool UAceWeaponComponent::CanEquip() const
{
    return true; // TODO сделать проверку на перезарядку и экипировку в процессе
}

bool UAceWeaponComponent::CanFire() const
{
    return true;
}

bool UAceWeaponComponent::CanReload() const
{
    return CurrentWeapon &&  CurrentWeapon->CanReload();
}
