// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "UI/AceBaseWidget.h"
#include "AceInventoryWeaponSlotWidget.generated.h"

class UImage;
class UTextBlock;
class UAceInventoryAttachmentSlotWidget;
class UAceBaseItemObject;
class AAcePlayerCharacter;
class UAceARItemObject;
class UAceAttachmentItemObject;

UCLASS()
class ACE_API UAceInventoryWeaponSlotWidget : public UAceBaseWidget
{
	GENERATED_BODY()
    
public:
    void AddAttachmentToItemObject(UAceAttachmentItemObject* AttachmentItemObject);
    void DeleteAttachmentFromItemObject(UAceAttachmentItemObject* AttachmentItemObject);
    
protected:
    UPROPERTY(meta=(BindWidget))
    UImage* ItemImage;

    UPROPERTY(meta=(BindWidget))
    UAceInventoryAttachmentSlotWidget* SightSlot;

    UPROPERTY(meta=(BindWidget))
    UAceInventoryAttachmentSlotWidget* SilencerSlot;

    UPROPERTY(meta=(BindWidget))
    UAceInventoryAttachmentSlotWidget* GripSlot;

    virtual void NativeOnInitialized() override;
    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
    virtual void ClearSlotAndDestroy(const bool DeleteInfoAboutAttachment = false) override;

    UFUNCTION()
    void AddWeaponWithoutSpawn(UAceBaseItemObject* Item, int32 IndexOfSlot);
    
    void AddWeapon(UAceARItemObject* WeaponItemObject);
    void SetWidgetProperties(const UAceARItemObject* Item);
    void SetIconToAttachmentSlot(const UAceARItemObject* Item);
    
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Settings")
    int32 IndexOfSlot;

    UAceBaseItemObject* ItemObject;
    
private:

};
