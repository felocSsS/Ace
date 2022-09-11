// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AceInventoryWeaponSlotWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class ACE_API UAceInventoryWeaponSlotWidget : public UUserWidget
{
	GENERATED_BODY()
    
public:
    UPROPERTY(meta=(BindWidget))
    UImage* ItemImage;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* ItemName;
protected:
    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Settings")
    int32 IndexOfSlot;
private:	
};
