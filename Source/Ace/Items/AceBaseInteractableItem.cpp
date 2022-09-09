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
    ItemObject = NewObject<UAceARItemObject>(this);
    if (!ItemObject) return;

    ItemObject->SetClass(ItemClass->StaticClass());
    ItemObject->SetIcon(Icon);
    ItemObject->SetName(ItemName);
}
