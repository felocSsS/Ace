// Ace Game. All Rights Reserved.


#include "Weapon/Attachments/AceSilencerAttachment.h"
#include "Components/AceInventoryComponent.h"
#include "Objects/WeaponItemObject/Attachments/AceSilencerAttachmentItemObject.h"
#include "Player/AcePlayerCharacter.h"

void AAceSilencerAttachment::BeginPlay()
{
    Super::BeginPlay();
    
    if (!ItemObject) GetDefaultItemObject();
}

void AAceSilencerAttachment::GetDefaultItemObject()
{
    ItemObject = NewObject<UAceSilencerAttachmentItemObject>(this);
    if (!ItemObject) return;
    
    ItemObject->ItemClass = AAceSilencerAttachment::StaticClass();
    
    Super::GetDefaultItemObject();
}
