// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "AceInventoryItemSlotWidget.generated.h"

class UAceBaseItemObject;
class UImage;
class UTextBlock;

UCLASS()
class ACE_API UAceInventoryItemSlotWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
    
public:
    
protected:
    UPROPERTY(meta=(BindWidget))
    UImage* ItemImage;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* ItemName;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* ItemCount;
    
    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

    UAceBaseItemObject* ItemObject;
    
private:
};
