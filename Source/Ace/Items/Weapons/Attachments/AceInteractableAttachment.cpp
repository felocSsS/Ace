// Ace Game. All Rights Reserved.

#include "Items/Weapons/Attachments/AceInteractableAttachment.h"
#include "Items/Objects/WeaponItemObject/Attachment/AceAttachmentItemObject.h"

void AAceInteractableAttachment::GetDefaultItemObject()
{
    if (!SpawnClass) return;
    
    const auto NewItemObject = NewObject<UAceAttachmentItemObject>(this);
    if (!NewItemObject) return;

    NewItemObject->SetClass(SpawnClass);
    NewItemObject->SetIcon(Icon);
    NewItemObject->SetName(ItemName);
    NewItemObject->AttachmentType = Cast<AAceBaseWeaponAttachment>(SpawnClass->GetDefaultObject())->AttachmentType;

    ItemObject = NewItemObject;
}
