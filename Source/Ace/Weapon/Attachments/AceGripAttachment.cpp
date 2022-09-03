// Ace Game. All Rights Reserved.


#include "Weapon/Attachments/AceGripAttachment.h"

#include "Components/AceInventoryComponent.h"
#include "Objects/WeaponItemObject/Attachments/AceGripAttachmentItemObject.h"
#include "Player/AcePlayerCharacter.h"

void AAceGripAttachment::BeginPlay()
{
    Super::BeginPlay();
}

void AAceGripAttachment::GetDefaultItemObject()
{
    ItemObject = NewObject<UAceGripAttachmentItemObject>(this);
    if (!ItemObject) return;
    
    ItemObject->ItemClass = AAceGripAttachment::StaticClass();

    Super::GetDefaultItemObject();
}
