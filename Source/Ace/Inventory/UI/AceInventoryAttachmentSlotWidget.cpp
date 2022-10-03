// Ace Game. All Rights Reserved.

#include "Inventory/UI/AceInventoryAttachmentSlotWidget.h"
#include "AceInventoryGridWidget.h"
#include "AceInventoryWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/AceWeaponComponent.h"
#include "Player/AcePlayerCharacter.h"
#include "Components/Image.h"
#include "Objects/AceBaseItemObject.h"
#include "Objects/WeaponItemObject/Attachment/AceAttachmentItemObject.h"
#include "UI/AceGameHUD.h"
#include "Weapon/AceBaseWeapon.h"

bool UAceInventoryAttachmentSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                                     UDragDropOperation* InOperation)
{
    Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

    const auto AttachmentItemObject = Cast<UAceAttachmentItemObject>(InOperation->Payload);
    
    if (AttachmentItemObject->AttachmentType == SlotAttachmentType)
    {
        SetIconAndSpawn(Cast<UAceAttachmentItemObject>(InOperation->Payload));
        HUD->GetInventory()->InventoryGrid->DeleteItemFromWidget(AttachmentItemObject);
    }
    
    return true;
}

void UAceInventoryAttachmentSlotWidget::SetIconAndSpawn(UAceAttachmentItemObject* AttachemntItemObject)
{
    if (!AttachemntItemObject && !Character) return;
        
    ItemImage->SetBrushFromTexture(AttachemntItemObject->GetObjectIcon());
    ItemImage->SetBrushTintColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
    Character->WeaponComponent->GetWeaponAtIndex(WeaponIndex)->SpawnAttachment(AttachemntItemObject->GetObjectClass(), SocketName);
    ItemObject = AttachemntItemObject;
}

void UAceInventoryAttachmentSlotWidget::SetIcon(UAceBaseItemObject* Attachemnt)
{
    if (!Attachemnt) return;
    
    auto AttachemntItemObject = Cast<UAceAttachmentItemObject>(Attachemnt);
    if (!AttachemntItemObject) return;

    if (AttachemntItemObject->AttachmentType == SlotAttachmentType) return;
    
    ItemImage->SetBrushFromTexture(AttachemntItemObject->GetObjectIcon());
    ItemImage->SetBrushTintColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
    ItemObject = AttachemntItemObject;
}

void UAceInventoryAttachmentSlotWidget::ClearSlot()
{
    ItemImage->SetBrushTintColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
    ItemObject = nullptr;
}
