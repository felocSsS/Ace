// Ace Game. All Rights Reserved.

#include "Weapon/Attachments/AceGripAttachment.h"
#include "Objects/WeaponItemObject/Attachments/AceGripAttachmentItemObject.h"

void AAceGripAttachment::BeginPlay()
{
    Super::BeginPlay();
}

void AAceGripAttachment::GetDefaultItemObject()
{
    ItemObject = NewObject<UAceGripAttachmentItemObject>(this);
    if (!ItemObject) return;
    
    ItemObject->SetClass(this->StaticClass());
    ItemObject->SetIcon(Icon);
    ItemObject->SetName(ItemName);
}
