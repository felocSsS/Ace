// Ace Game. All Rights Reserved.

#include "Inventory/UI/AceInventoryWeaponSlotWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/AceWeaponComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
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
}

bool UAceInventoryWeaponSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                                 UDragDropOperation* InOperation)
{
    Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

    const auto Character = Cast<AAcePlayerCharacter>(GetOwningPlayerPawn());
    const auto Payload = Cast<UAceARItemObject>(InOperation->Payload);
    if (!GetWorld() || !Character || !Payload) return false;
    
    ItemImage->SetBrushFromTexture(Payload->GetObjectIcon());
    ItemImage->SetBrushTintColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
    /*ItemName->SetText(Payload->GetObjectName());*/
    
    !Payload->IsASightAvailable ? SightSlot->SetVisibility(ESlateVisibility::Visible) : SightSlot->SetVisibility(ESlateVisibility::Collapsed); 
    !Payload->IsAGripAvailable ? GripSlot->SetVisibility(ESlateVisibility::Visible) : GripSlot->SetVisibility(ESlateVisibility::Collapsed); 
    !Payload->IsASilencerAvailable ? SilencerSlot->SetVisibility(ESlateVisibility::Visible) : SilencerSlot->SetVisibility(ESlateVisibility::Collapsed);

    ItemObject = Payload;
    
    Character->WeaponComponent->AddWeapon(Payload->GetObjectClass(), IndexOfSlot);

    return true;
}
