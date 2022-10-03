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
    
protected:
    virtual void NativeOnInitialized() override;

    UFUNCTION()
    void AddItemToGrid(UAceBaseItemObject* Item);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=UI)
    TSubclassOf<UAceInventoryItemSlotWidget> ItemClass;
    
private:
    int32 SlotsInRow = 10;
    TArray<UAceBaseItemObject*> Items;
};
