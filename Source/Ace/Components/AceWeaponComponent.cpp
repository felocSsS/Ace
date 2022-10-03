// Ace Game. All Rights Reserved.

#include "Components/AceWeaponComponent.h"
#include "Items/AceBaseItem.h"
#include "AceInventoryComponent.h"
#include "GameFramework/Character.h"
#include "Objects/AceBaseItemObject.h"
#include "Player/AcePlayerCharacter.h"
#include "Weapon/AceBaseWeapon.h"
#include "Objects/WeaponItemObject/AceARItemObject.h"

UAceWeaponComponent::UAceWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAceWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

    //Weapons.SetNum(2);
    
    CurrentWeaponIndex = 0;
    SpawnStartWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void UAceWeaponComponent::SpawnStartWeapons()
{
    AAcePlayerCharacter* Character = Cast<AAcePlayerCharacter>(GetOwner());
    
    if(!Character || !GetWorld()) return;

    for (int32 i = 0; i < StartWeapons.Num(); ++i)
    {
        auto SpawnedWeapon = GetWorld()->SpawnActor<AAceBaseWeapon>(StartWeapons[i].WeaponClass);
        if(!SpawnedWeapon) return;
        
        SpawnedWeapon->SetOwner(Character);
        SpawnedWeapon->SpawnStartAttachment();
        Weapons.Add(SpawnedWeapon);
        Character->InventoryComponent->AddItem(SpawnedWeapon->GetItemObject());

        NotyfyWidgetAboutAddingWeapon.Broadcast(SpawnedWeapon->GetItemObject(), i);
        
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
    CurrentWeapon = Weapons[WeaponIndex];
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), "RightHandSocket");
    CurrentWeaponChangedDelegate.Broadcast(CurrentWeapon);
}

void UAceWeaponComponent::AddWeapon(UAceARItemObject* Item, int32 AtIndex)
{
    if (!Item || !GetWorld()) return;

    AAcePlayerCharacter* Character = Cast<AAcePlayerCharacter>(GetOwner());
    if (!Character) return;
    
    const auto Weapon = GetWorld()->SpawnActor<AAceBaseWeapon>(Item->GetObjectClass());
    if (!Weapon) return;

    Weapon->SetOwner(Character);
    Weapon->SpawnAttachmentsFromItemObject(Item->CurrentAttachemnts);
    
    if (Weapons.IsValidIndex(AtIndex))
    {
        Weapons[AtIndex]->DestroyWeapon();
        Weapons[AtIndex] = Weapon;   
    }
    else
    {
        Weapons.SetNum(Weapons.Num() +1);
        if(Weapons[AtIndex])
        {
            Weapons[AtIndex]->DestroyWeapon();   
        }
        Weapons[AtIndex] = Weapon;
    }

    EquipWeapon(AtIndex);
}

AAceBaseWeapon* UAceWeaponComponent::GetWeaponAtIndex(int32 Index)
{
    if (Weapons.IsValidIndex(Index))
    {
        return Weapons[Index];
    }

    return nullptr;
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
    if (!CurrentWeapon) return;

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
    if (Weapons.IsValidIndex(CurrentWeaponIndex))
    {
        EquipWeapon(CurrentWeaponIndex);   
    }
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
