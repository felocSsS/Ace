// Ace Game. All Rights Reserved.


#include "Inventory/UI/AceInventoryWeaponSlotWidget.h"

#include "Blueprint/DragDropOperation.h"
#include "Components/AceWeaponComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Objects/WeaponItemObject/AceARItemObject.h"
#include "Player/AcePlayerCharacter.h"
#include "Weapon/AceBaseWeapon.h"

bool UAceInventoryWeaponSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                                 UDragDropOperation* InOperation)
{
    Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

    const auto Character = Cast<AAcePlayerCharacter>(GetOwningPlayerPawn());
    const auto Payload = Cast<UAceARItemObject>(InOperation->Payload);
    if (!GetWorld() || !Character || !Payload) return false;
    
    ItemImage->SetBrushFromTexture(Payload->GetObjectIcon());
    ItemName->SetText(Payload->GetObjectName());
    
    const auto Item = GetWorld()->SpawnActor<AAceBaseWeapon>(Payload->GetObjectClass());
    if (!Item) return false;
    
    Item->SetOwner(Character);
    Character->WeaponComponent->AddWeapon(Item, IndexOfSlot);
    Character->WeaponComponent->EquipWeapon(IndexOfSlot);

    return true;
}
