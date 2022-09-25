// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AceInventoryItemSlotWidget.generated.h"

class UAceBaseItemObject;
class UImage;

UCLASS()
class ACE_API UAceInventoryItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()
    
public:
    void OnItemSpawned(UAceBaseItemObject* Item);
    
protected:
    UPROPERTY(meta=(BindWidget))
    UImage* ItemImage;

    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

    UAceBaseItemObject* ItemObject;
    
private:
    
};
