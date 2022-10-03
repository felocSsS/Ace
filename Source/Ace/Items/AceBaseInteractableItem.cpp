// Ace Game. All Rights Reserved.

#include "AceBaseInteractableItem.h"
#include "Components/BoxComponent.h"
#include "Objects/WeaponItemObject/AceARItemObject.h"

AAceBaseInteractableItem::AAceBaseInteractableItem()
{
    ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    SetRootComponent(ItemMesh);

    CollisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
    CollisionBox->SetupAttachment(ItemMesh);
    CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel3);
}

void AAceBaseInteractableItem::GetDefaultItemObject()
{
    ItemObject = NewObject<UAceBaseItemObject>(this);
}
