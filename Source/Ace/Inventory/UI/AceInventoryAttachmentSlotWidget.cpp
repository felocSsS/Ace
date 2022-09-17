// Ace Game. All Rights Reserved.


#include "Inventory/UI/AceInventoryAttachmentSlotWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/AceWeaponComponent.h"
#include "Player/AcePlayerCharacter.h"
#include "Components/Image.h"
#include "Objects/AceBaseItemObject.h"
#include "Weapon/AceBaseWeapon.h"

bool UAceInventoryAttachmentSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                                     UDragDropOperation* InOperation)
{
    Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

    const auto Character = Cast<AAcePlayerCharacter>(GetOwningPlayerPawn());
    const auto Payload = Cast<UAceBaseItemObject>(InOperation->Payload);
    if (!Character || !Payload) return false;
    
    if (Payload->IsA(ItemClassOfThisSlot))
    {
        ItemImage->SetBrushFromTexture(Payload->GetObjectIcon());
        ItemImage->SetBrushTintColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
        
        Character->WeaponComponent->GetWeaponAtIndex(WeaponIndex)->SpawnAttachment(Payload->GetObjectClass(), SocketName);
    }

    return true;
}
