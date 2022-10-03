// Ace Game. All Rights Reserved.

#include "Inventory/UI/AceInventoryGridWidget.h"
#include "AceInventoryItemSlotWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/AceInventoryComponent.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Player/AcePlayerCharacter.h"
#include "Objects/AceBaseItemObject.h"

void UAceInventoryGridWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    GridPanel->ClearChildren();
    
    if (Character)
        Character->InventoryComponent->OnItemAdded.AddDynamic(this, &UAceInventoryGridWidget::AddItemToGrid);
}

void UAceInventoryGridWidget::SpawnAllItems()
{
    if (!GetWorld() && !Character) return;

    auto AllItems = Character->InventoryComponent->GetAllItems();

    for (int32 i = 0; i < AllItems.Num(); ++i)
    {
        auto CreatedItemWidget = CreateWidget<UAceInventoryItemSlotWidget>(GetWorld(), ItemClass);
        if (!CreatedItemWidget) return;
        
        CreatedItemWidget->OnItemSpawned(AllItems[i]);
        
        GridPanel->AddChildToUniformGrid(CreatedItemWidget, i / SlotsInRow, i % SlotsInRow);
    }
}

void UAceInventoryGridWidget::AddItemToGrid(UAceBaseItemObject* Item)
{
    auto CreatedItemWidget = CreateWidget<UAceInventoryItemSlotWidget>(GetWorld(), ItemClass);
    if (!CreatedItemWidget) return;
    
    CreatedItemWidget->OnItemSpawned(Item);
        
    GridPanel->AddChildToUniformGrid(CreatedItemWidget, Items.Num() / SlotsInRow, Items.Num() % SlotsInRow);
    Items.Add(Item);
}

void UAceInventoryGridWidget::DeleteItemFromWidget(UAceBaseItemObject* Item)
{
    if (!Items.Contains(Item)) return;
    
    int32 Index = Items.Find(Item);
    GridPanel->RemoveChildAt(Index);
    Items.Remove(Item);
    SortItems(Index);
}

void UAceInventoryGridWidget::SortItems()
{
    
}

void UAceInventoryGridWidget::SortItems(int32 AtIndex)
{
    for (int32 i = AtIndex; i < Items.Num(); i++)
    {
        auto GridSlot = UWidgetLayoutLibrary::SlotAsUniformGridSlot(GridPanel->GetChildAt(i));
        if(GridSlot)
        {
            GridSlot->SetRow(i / SlotsInRow);
            GridSlot->SetColumn(i % SlotsInRow);   
        }
    }
}
