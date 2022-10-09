// Ace Game. All Rights Reserved.

#include "Inventory/UI/AceInventoryAttachmentSlotWidget.h"
#include "AceInventoryGridWidget.h"
#include "AceInventoryWeaponSlotWidget.h"
#include "AceInventoryWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/AceWeaponComponent.h"
#include "Player/AcePlayerCharacter.h"
#include "Components/Image.h"
#include "Inventory/AceInventoryDragDropOperation.h"
#include "Objects/AceBaseItemObject.h"
#include "Objects/WeaponItemObject/Attachment/AceAttachmentItemObject.h"
#include "UI/AceGameHUD.h"
#include "Weapon/AceBaseWeapon.h"

bool UAceInventoryAttachmentSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                                     UDragDropOperation* InOperation)
{
    Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

    const auto AttachmentItemObject = Cast<UAceAttachmentItemObject>(InOperation->Payload);
    
    if (AttachmentItemObject && AttachmentItemObject != ItemObject && AttachmentItemObject->AttachmentType == SlotAttachmentType)
    {
        if (ItemObject)
        {
            HUD->GetInventory()->InventoryGrid->AddItemToGrid(ItemObject); 
            ClearSlotAndDestroy();
        }
        SetIconAndSpawn(AttachmentItemObject);
        HUD->GetInventory()->InventoryGrid->DeleteItemFromWidget(AttachmentItemObject);
        OwnerWidget->AddAttachmentToItemObject(AttachmentItemObject);
    }
    
    return true;
}

FReply UAceInventoryAttachmentSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

    FEventReply Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
    
    return Reply.NativeReply;
}

void UAceInventoryAttachmentSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
    Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

    const auto DragOperation = Cast<UAceInventoryDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(UAceInventoryDragDropOperation::StaticClass()));
    DragOperation->Payload = ItemObject;
    DragOperation->DefaultDragVisual = this;
    DragOperation->Pivot = EDragPivot::CenterCenter;
    DragOperation->WidgetFrom = this;

    OutOperation = DragOperation;
}

void UAceInventoryAttachmentSlotWidget::SetIconAndSpawn(UAceAttachmentItemObject* AttachmentItemObject)
{
    if (!AttachmentItemObject && !Character) return;
        
    ItemImage->SetBrushFromTexture(AttachmentItemObject->GetObjectIcon());
    ItemImage->SetBrushTintColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
    Character->WeaponComponent->GetWeaponAtIndex(WeaponIndex)->SpawnAttachment(AttachmentItemObject->GetObjectClass(), SocketName);
    ItemObject = AttachmentItemObject;
}

void UAceInventoryAttachmentSlotWidget::SetIcon(UAceAttachmentItemObject* AttachmentItemObject)
{
    if (!AttachmentItemObject) return;
    
    if (AttachmentItemObject->AttachmentType != SlotAttachmentType) return;
    
    ItemImage->SetBrushFromTexture(AttachmentItemObject->GetObjectIcon());
    ItemImage->SetBrushTintColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
    ItemObject = AttachmentItemObject;
}

void UAceInventoryAttachmentSlotWidget::ClearSlot()
{
    ItemImage->SetBrushTintColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
    ItemObject = nullptr;
}

void UAceInventoryAttachmentSlotWidget::ClearSlotAndDestroy(const bool DeleteIntoAboutAttachment)
{
    ItemImage->SetBrushTintColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
    Character->WeaponComponent->GetWeaponAtIndex(WeaponIndex)->DestroyAttachment(ItemObject);
    if (DeleteIntoAboutAttachment)
        OwnerWidget->DeleteAttachmentFromItemObject(ItemObject);
    ItemObject = nullptr;
}

