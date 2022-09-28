// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AceInventoryWeaponSlotWidget.generated.h"

class UImage;
class UTextBlock;
class UAceInventoryAttachmentSlotWidget;
class UAceBaseItemObject;
class AAcePlayerCharacter;
class UAceARItemObject;

UCLASS()
class ACE_API UAceInventoryWeaponSlotWidget : public UUserWidget
{
	GENERATED_BODY()
    
public:

protected:
    UPROPERTY(meta=(BindWidget))
    UImage* ItemImage;

    /*UPROPERTY(meta=(BindWidget))
    UTextBlock* ItemName;*/

    UPROPERTY(meta=(BindWidget))
    UAceInventoryAttachmentSlotWidget* SightSlot;

    UPROPERTY(meta=(BindWidget))
    UAceInventoryAttachmentSlotWidget* SilencerSlot;

    UPROPERTY(meta=(BindWidget))
    UAceInventoryAttachmentSlotWidget* GripSlot;

    virtual void NativeOnInitialized() override;
    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

    UFUNCTION()
    void AddWeaponWithoutSpawn(UAceBaseItemObject* Item, int32 IndexOfSlot);
    
    void AddWeapon(UAceARItemObject* Item);
    void SetWidgetProperties(const UAceARItemObject* Item);
    void SetIconToAttachmentSlot(const UAceARItemObject* Item);
    
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Settings")
    int32 IndexOfSlot;

    UAceBaseItemObject* ItemObject;
    
private:
    AAcePlayerCharacter* Character;
};
