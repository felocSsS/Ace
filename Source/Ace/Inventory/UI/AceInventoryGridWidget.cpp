// Ace Game. All Rights Reserved.

#include "Inventory/UI/AceInventoryGridWidget.h"

#include "Components/AceInventoryComponent.h"
#include "Components/UniformGridPanel.h"
#include "Player/AcePlayerCharacter.h"

void UAceInventoryGridWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    GridPanel->ClearChildren();
}

void UAceInventoryGridWidget::NativeConstruct()
{
    Super::NativeConstruct();
    GridPanel->ClearChildren();
    SpawnAllItems();
}

void UAceInventoryGridWidget::SpawnAllItems()
{
    if (!GetWorld()) return;
    
    Character = Cast<AAcePlayerCharacter>(GetOwningPlayerPawn());
    if (!Character) return;

    auto AllItems = Character->InventoryComponent->GetAllItems();

    for (int32 i = 0; i < AllItems.Num(); ++i)
    {
        auto CreatedItemWidget = CreateWidget<UAceInventoryItemSlotWidget>(GetWorld(), ItemClass);
        if (!CreatedItemWidget) return;
        
        CreatedItemWidget->OnItemSpawned(AllItems[i]);
        
        GridPanel->AddChildToUniformGrid(CreatedItemWidget, i / SlotsInRow, i % SlotsInRow);
    }
}

