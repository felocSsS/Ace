// Ace Game. All Rights Reserved.

#include "Inventory/UI/AceInventoryAttachmentSlotWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/AceWeaponComponent.h"
#include "Player/AcePlayerCharacter.h"
#include "Components/Image.h"
#include "Objects/AceBaseItemObject.h"
#include "Objects/WeaponItemObject/Attachment/AceAttachmentItemObject.h"
#include "Weapon/AceBaseWeapon.h"

bool UAceInventoryAttachmentSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                                     UDragDropOperation* InOperation)
{
    Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

    SetIconAndSpawn(InOperation->Payload);
    
    return true;
}

void UAceInventoryAttachmentSlotWidget::SetIconAndSpawn(UObject* Attachemnt)
{
    if (!Attachemnt) return;
    
    auto AttachemntItemObject = Cast<UAceAttachmentItemObject>(Attachemnt);
    if (!AttachemntItemObject) return;

    if (AttachemntItemObject->AttachmentType == SlotAttachmentType)
    {
        const auto Character = Cast<AAcePlayerCharacter>(GetOwningPlayerPawn());
        if (!Character) return;
        
        ItemImage->SetBrushFromTexture(AttachemntItemObject->GetObjectIcon());
        ItemImage->SetBrushTintColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
        Character->WeaponComponent->GetWeaponAtIndex(WeaponIndex)->SpawnAttachment(AttachemntItemObject->GetObjectClass(), SocketName);
        ItemObject = AttachemntItemObject;
    }
}

void UAceInventoryAttachmentSlotWidget::SetIcon(UObject* Attachemnt)
{
    if (!Attachemnt) return;
    
    auto AttachemntItemObject = Cast<UAceAttachmentItemObject>(Attachemnt);
    if (!AttachemntItemObject) return;

    if (AttachemntItemObject->AttachmentType == SlotAttachmentType)
    {
        ItemImage->SetBrushFromTexture(AttachemntItemObject->GetObjectIcon());
        ItemImage->SetBrushTintColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
        ItemObject = AttachemntItemObject;
    }
}

void UAceInventoryAttachmentSlotWidget::ClearSlot()
{
    ItemImage->SetBrushTintColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
    ItemObject = nullptr;
}
