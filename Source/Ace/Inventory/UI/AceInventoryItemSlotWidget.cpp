// Ace Game. All Rights Reserved.

#include "Inventory/UI/AceInventoryItemSlotWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Objects/AceBaseItemObject.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UAceInventoryItemSlotWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    ItemObject = Cast<UAceBaseItemObject>(ListItemObject);
    ItemImage->SetBrushFromTexture(ItemObject->GetObjectIcon());
    ItemName->SetText(ItemObject->GetObjectName());
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
    
    const auto DragOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
    DragOperation->Payload = ItemObject;
    DragOperation->DefaultDragVisual = this;
    DragOperation->Pivot = EDragPivot::CenterCenter;

    OutOperation = DragOperation;
}
