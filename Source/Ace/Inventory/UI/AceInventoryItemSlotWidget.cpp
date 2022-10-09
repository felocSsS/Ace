// Ace Game. All Rights Reserved.

#include "Inventory/UI/AceInventoryItemSlotWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Objects/AceBaseItemObject.h"
#include "Components/Image.h"
#include "Inventory/AceInventoryDragDropOperation.h"

void UAceInventoryItemSlotWidget::OnItemSpawned(UAceBaseItemObject* Item)
{
    if (!Item) return;
    
    ItemObject = Item;
    ItemImage->SetBrushFromTexture(Item->GetObjectIcon());
}

FReply UAceInventoryItemSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
    
    FEventReply Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
    
    return Reply.NativeReply;
}

void UAceInventoryItemSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
    UDragDropOperation*& OutOperation)
{
    Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

    const auto DragOperation = Cast<UAceInventoryDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(UAceInventoryDragDropOperation::StaticClass()));
    DragOperation->Payload = ItemObject;
    DragOperation->DefaultDragVisual = this;
    DragOperation->Pivot = EDragPivot::CenterCenter;
    DragOperation->WidgetFrom = this;

    OutOperation = DragOperation;
}
