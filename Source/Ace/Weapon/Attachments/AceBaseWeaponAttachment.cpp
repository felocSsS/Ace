// Ace Game. All Rights Reserved.

#include "Weapon/Attachments/AceBaseWeaponAttachment.h"
#include "Components/StaticMeshComponent.h"
#include "Objects/WeaponItemObject/Attachment/AceAttachmentItemObject.h"

AAceBaseWeaponAttachment::AAceBaseWeaponAttachment()
{
	PrimaryActorTick.bCanEverTick = false;

    AttachmentMesh = CreateDefaultSubobject<UStaticMeshComponent>("AttachmentMesh");
    AttachmentMesh->SetupAttachment(RootComponent);
}

void AAceBaseWeaponAttachment::GetDefaultItemObject()
{
    auto NewItemObject = NewObject<UAceAttachmentItemObject>(this);
    if (!NewItemObject) return;

    NewItemObject->SetClass(SpawnClass);
    NewItemObject->SetIcon(Icon);
    NewItemObject->SetName(ItemName);
    NewItemObject->AttachmentType = AttachmentType;
    
    ItemObject = NewItemObject;
}

FTransform AAceBaseWeaponAttachment::GetAttachmentSocket(FName SocketName) const
{
    if (!AttachmentMesh) return FTransform();

    return AttachmentMesh->GetSocketTransform(SocketName);
}
