// Ace Game. All Rights Reserved.

#include "AceBaseInteractableItem.h"
#include "Components/BoxComponent.h"
#include "Objects/WeaponItemObject/AceARItemObject.h"
#include "Weapon/AceBaseWeapon.h"

AAceBaseInteractableItem::AAceBaseInteractableItem()
{
    ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
    SetRootComponent(ItemMesh);

    CollisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
    CollisionBox->SetupAttachment(ItemMesh);
    CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel3);
}

void AAceBaseInteractableItem::BeginPlay()
{
    Super::BeginPlay();
}

void AAceBaseInteractableItem::GetDefaultItemObject()
{
    const auto NewItemObject = NewObject<UAceARItemObject>(this);
    if (!NewItemObject) return;

    NewItemObject->SetClass(SpawnClass);
    NewItemObject->SetIcon(Icon);
    NewItemObject->SetName(ItemName);
    const auto WeaponClass = Cast<AAceBaseWeapon>(SpawnClass->ClassDefaultObject);
    NewItemObject->IsASightAvailable = WeaponClass->IsASightAvailable;
    NewItemObject->IsASilencerAvailable = WeaponClass->IsASilencerAvailable;
    NewItemObject->IsAGripAvailable = WeaponClass->IsAGripAvailable;

    ItemObject = NewItemObject;
}
