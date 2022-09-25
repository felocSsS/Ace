// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AceInventoryItemSlotWidget.h"
#include "Blueprint/UserWidget.h"
#include "AceInventoryGridWidget.generated.h"

class UUniformGridPanel;
class AAcePlayerCharacter;

UCLASS()
class ACE_API UAceInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(meta=(BindWidget))
    UUniformGridPanel* GridPanel;
    
    void SpawnAllItems();
    
protected:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=UI)
    TSubclassOf<UAceInventoryItemSlotWidget> ItemClass;

    AAcePlayerCharacter* Character;
    
private:
    int32 SlotsInRow = 10;
};
