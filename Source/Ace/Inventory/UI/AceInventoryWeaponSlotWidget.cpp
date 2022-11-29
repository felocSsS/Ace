// Ace Game. All Rights Reserved.

#include "Inventory/UI/AceInventoryWeaponSlotWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/AceWeaponComponent.h"
#include "Components/Image.h"
#include "Items/Objects/WeaponItemObject/AceARItemObject.h"
#include "Player/AcePlayerCharacter.h"
#include "AceInventoryAttachmentSlotWidget.h"
#include "AceInventoryWidget.h"
#include "UI/AceGameHUD.h"
#include "Inventory/UI/AceInventoryGridWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Inventory/AceInventoryDragDropOperation.h"
#include "Items/Objects/WeaponItemObject/Attachment/AceAttachmentItemObject.h"

void UAceInventoryWeaponSlotWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    SightSlot->SetVisibility(ESlateVisibility::Collapsed);
    SightSlot->WeaponIndex = IndexOfSlot;
    SightSlot->OwnerWidget = this;

    SilencerSlot->SetVisibility(ESlateVisibility::Collapsed);
    SilencerSlot->WeaponIndex = IndexOfSlot;
    SilencerSlot->OwnerWidget = this;

    GripSlot->SetVisibility(ESlateVisibility::Collapsed);
    GripSlot->WeaponIndex = IndexOfSlot;
    GripSlot->OwnerWidget = this;
    
    if (Character)
        Character->WeaponComponent->NotyfyWidgetAboutAddingWeapon.AddDynamic(this, &UAceInventoryWeaponSlotWidget::AddWeaponWithoutSpawn);
}

bool UAceInventoryWeaponSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                                 UDragDropOperation* InOperation)
{
    Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

    const auto AceDragAndDropOperation = Cast<UAceInventoryDragDropOperation>(InOperation);
    const auto WeaponItemObject = Cast<UAceARItemObject>(InOperation->Payload);
    
    if (WeaponItemObject && AceDragAndDropOperation && WeaponItemObject != ItemObject)
    {
        if (ItemObject)
            HUD->GetInventory()->InventoryGrid->AddItemToGrid(ItemObject); 
        HUD->GetInventory()->InventoryGrid->DeleteItemFromWidget(WeaponItemObject);
        AddWeapon(WeaponItemObject);
        AceDragAndDropOperation->WidgetFrom->ClearSlotAndDestroy();
    }
    
    return true;
}

FReply UAceInventoryWeaponSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

    FEventReply Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
    
    return Reply.NativeReply;
}

void UAceInventoryWeaponSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
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

void UAceInventoryWeaponSlotWidget::ClearSlotAndDestroy(const bool DeleteInfoAboutAttachment)
{
    SightSlot->ClearSlotAndDestroy();
    SightSlot->SetVisibility(ESlateVisibility::Collapsed);
    SilencerSlot->ClearSlotAndDestroy();
    SilencerSlot->SetVisibility(ESlateVisibility::Collapsed);
    GripSlot->ClearSlotAndDestroy();
    GripSlot->SetVisibility(ESlateVisibility::Collapsed);

    ItemImage->SetBrushTintColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));

    Character->WeaponComponent->DestoyWeapon(IndexOfSlot);
    ItemObject = nullptr;
}

void UAceInventoryWeaponSlotWidget::AddWeapon(UAceARItemObject* WeaponItemObject)
{
    if (!WeaponItemObject || !Character) return;

    SetWidgetProperties(WeaponItemObject);
    SetIconToAttachmentSlot(WeaponItemObject);

    ItemObject = WeaponItemObject;

    Character->WeaponComponent->AddWeapon(WeaponItemObject, IndexOfSlot);
}

void UAceInventoryWeaponSlotWidget::AddWeaponWithoutSpawn(UAceBaseItemObject* WeaponItemObject, int32 Index)
{
    if (!WeaponItemObject || IndexOfSlot != Index) return;

    const auto ItemAR = Cast<UAceARItemObject>(WeaponItemObject);
    if (!ItemAR) return;

    SetWidgetProperties(ItemAR);
    SetIconToAttachmentSlot(ItemAR);

    ItemObject = ItemAR; 
}

void UAceInventoryWeaponSlotWidget::SetWidgetProperties(const UAceARItemObject* Item)
{
    if (!Item) return;
    
    ItemImage->SetBrushFromTexture(Item->GetObjectIcon());
    ItemImage->SetBrushTintColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
    
    !Item->IsASightAvailable ? SightSlot->SetVisibility(ESlateVisibility::Visible) : SightSlot->SetVisibility(ESlateVisibility::Collapsed); 
    !Item->IsAGripAvailable ? GripSlot->SetVisibility(ESlateVisibility::Visible) : GripSlot->SetVisibility(ESlateVisibility::Collapsed); 
    !Item->IsASilencerAvailable ? SilencerSlot->SetVisibility(ESlateVisibility::Visible) : SilencerSlot->SetVisibility(ESlateVisibility::Collapsed);
}

void UAceInventoryWeaponSlotWidget::SetIconToAttachmentSlot(const UAceARItemObject* Item)
{
    if (Item->CurrentAttachemntsItemObjects.Sight)
        SightSlot->SetIcon(Item->CurrentAttachemntsItemObjects.Sight);   
    else
        SightSlot->ClearSlot();
        
    if (Item->CurrentAttachemntsItemObjects.Silencer)
        SilencerSlot->SetIcon(Item->CurrentAttachemntsItemObjects.Silencer);
    else
        SilencerSlot->ClearSlot();
    
    if (Item->CurrentAttachemntsItemObjects.Grip)
        GripSlot->SetIcon(Item->CurrentAttachemntsItemObjects.Grip);
    else
        GripSlot->ClearSlot();
}

void UAceInventoryWeaponSlotWidget::AddAttachmentToItemObject(UAceAttachmentItemObject* AttachmentItemObject)
{
    if (!AttachmentItemObject) return;

    const auto WeaponItemObject = Cast<UAceARItemObject>(ItemObject);
    switch (AttachmentItemObject->AttachmentType)
    {
        case EAttachmentType::Grip:
            WeaponItemObject->CurrentAttachemntsItemObjects.Grip = AttachmentItemObject;
            break;

        case EAttachmentType::Sight:
            WeaponItemObject->CurrentAttachemntsItemObjects.Sight = AttachmentItemObject;
            break;

        case EAttachmentType::Silencer:
            WeaponItemObject->CurrentAttachemntsItemObjects.Silencer = AttachmentItemObject;
            break;
    }
}

void UAceInventoryWeaponSlotWidget::DeleteAttachmentFromItemObject(UAceAttachmentItemObject* AttachmentItemObject)
{
    if (!AttachmentItemObject) return;

    const auto WeaponItemObject = Cast<UAceARItemObject>(ItemObject);
    switch (AttachmentItemObject->AttachmentType)
    {
    case EAttachmentType::Grip:
        WeaponItemObject->CurrentAttachemntsItemObjects.Grip = nullptr;
        break;

    case EAttachmentType::Sight:
        WeaponItemObject->CurrentAttachemntsItemObjects.Sight = nullptr;
        break;

    case EAttachmentType::Silencer:
        WeaponItemObject->CurrentAttachemntsItemObjects.Silencer = nullptr;
        break;
    }
}
