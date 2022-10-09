// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/AceBaseWidget.h"
#include "AceInventoryGridWidget.generated.h"

class UUniformGridPanel;
class AAcePlayerCharacter;
class UAceInventoryItemSlotWidget;
class UAceBaseItemObject;

UCLASS()
class ACE_API UAceInventoryGridWidget : public UAceBaseWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(meta=(BindWidget))
    UUniformGridPanel* GridPanel;
    
    void SpawnAllItems();
    void SortItems();
    void SortItems(int32 AtIndex);
    void DeleteItemFromWidget(UAceBaseItemObject* Item);
    UFUNCTION()
    void AddItemToGrid(UAceBaseItemObject* Item);
    
protected:
    virtual void NativeOnInitialized() override;

    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=UI)
    TSubclassOf<UAceInventoryItemSlotWidget> ItemClass;
    
private:
    int32 SlotsInRow = 9;
    TArray<UAceBaseItemObject*> Items;
};
