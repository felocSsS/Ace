// Ace Game. All Rights Reserved.

#include "Inventory/UI/AceInventoryWeaponSlotWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/AceWeaponComponent.h"
#include "Components/Image.h"
#include "Objects/WeaponItemObject/AceARItemObject.h"
#include "Player/AcePlayerCharacter.h"
#include "AceInventoryAttachmentSlotWidget.h"

void UAceInventoryWeaponSlotWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    SightSlot->SetVisibility(ESlateVisibility::Collapsed);
    SightSlot->WeaponIndex = IndexOfSlot;

    SilencerSlot->SetVisibility(ESlateVisibility::Collapsed);
    SilencerSlot->WeaponIndex = IndexOfSlot;

    GripSlot->SetVisibility(ESlateVisibility::Collapsed);
    GripSlot->WeaponIndex = IndexOfSlot;
    
    Character = Cast<AAcePlayerCharacter>(GetOwningPlayerPawn());
    if(Character)
    {
        Character->WeaponComponent->NotyfyWidgetAboutAddingWeapon.AddDynamic(this, &UAceInventoryWeaponSlotWidget::AddWeaponWithoutSpawn);   
    }
}

bool UAceInventoryWeaponSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                                 UDragDropOperation* InOperation)
{
    Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
    
    AddWeapon(Cast<UAceARItemObject>(InOperation->Payload));
    
    return true;
}

void UAceInventoryWeaponSlotWidget::AddWeapon(UAceARItemObject* Item)
{
    if (!Item || !Character) return;

    SetWidgetProperties(Item);
    
    SetIconToAttachmentSlot(Item);

    ItemObject = Item;

    Character->WeaponComponent->AddWeapon(Item, IndexOfSlot);
}

void UAceInventoryWeaponSlotWidget::AddWeaponWithoutSpawn(UAceBaseItemObject* Item, int32 Index)
{
    if (!Item || IndexOfSlot != Index) return;

    const auto ItemAR = Cast<UAceARItemObject>(Item);
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
    if (Item->CurrentAttachemnts.Sight)
        SightSlot->SetIcon(Item->CurrentAttachemnts.Sight->GetItemObject());
    else
        SightSlot->ClearSlot();
        
    if (Item->CurrentAttachemnts.Silencer)
        SilencerSlot->SetIcon(Item->CurrentAttachemnts.Silencer->GetItemObject());
    else
        SightSlot->ClearSlot();
    
    if (Item->CurrentAttachemnts.Grip)
        GripSlot->SetIcon(Item->CurrentAttachemnts.Grip->GetItemObject());
    else
        SightSlot->ClearSlot();
}

