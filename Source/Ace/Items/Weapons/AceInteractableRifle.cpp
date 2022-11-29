// Ace Game. All Rights Reserved.

#include "Items/Weapons/AceInteractableRifle.h"
#include "Items/Objects/WeaponItemObject/AceARItemObject.h"
#include "Weapon/AceBaseWeapon.h"

void AAceInteractableRifle::GetDefaultItemObject()
{
    if (!SpawnClass) return;
    
    const auto NewItemObject = NewObject<UAceARItemObject>(this);
    if (!NewItemObject) return;

    NewItemObject->SetClass(SpawnClass);
    NewItemObject->SetIcon(Icon);
    NewItemObject->SetName(ItemName);
    const auto Weapon = Cast<AAceBaseWeapon>(SpawnClass->GetDefaultObject());
    NewItemObject->IsAGripAvailable = Weapon->IsAGripAvailable;
    NewItemObject->IsASightAvailable = Weapon->IsASightAvailable;
    NewItemObject->IsASilencerAvailable = Weapon->IsASilencerAvailable;

    ItemObject = NewItemObject;
}
