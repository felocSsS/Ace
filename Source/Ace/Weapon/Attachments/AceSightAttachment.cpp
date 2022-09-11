// Ace Game. All Rights Reserved.

#include "Weapon/Attachments/AceSightAttachment.h"
#include "Objects/WeaponItemObject/Attachments/AceSightAttachmentItemObject.h"
#include "Player/AcePlayerCharacter.h"

void AAceSightAttachment::BeginPlay()
{
    Super::BeginPlay();
}

void AAceSightAttachment::GetDefaultItemObject()
{
    ItemObject = NewObject<UAceSightAttachmentItemObject>(this);
    if (!ItemObject) return;
    
    ItemObject->SetClass(SpawnClass);
    ItemObject->SetIcon(Icon);
    ItemObject->SetName(ItemName);
}
