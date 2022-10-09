// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/AceBaseWidget.h"
#include "Weapon/Attachments/AceBaseWeaponAttachment.h"
#include "AceInventoryAttachmentSlotWidget.generated.h"

class UImage;
class UAceBaseItemObject;
class UAceAttachmentItemObject;
class UAceInventoryWeaponSlotWidget;

UCLASS()
class ACE_API UAceInventoryAttachmentSlotWidget : public UAceBaseWidget
{
	GENERATED_BODY()
	    
public:
    int32 WeaponIndex;
    
    void SetIconAndSpawn(UAceAttachmentItemObject* AttachmentItemObject);
    void SetIcon(UAceAttachmentItemObject* AttachmentItemObject);
    void ClearSlot();
    virtual void ClearSlotAndDestroy(const bool DeleteInfoAboutAttachment = false) override;

    UAceInventoryWeaponSlotWidget* OwnerWidget;
    
protected:
    UPROPERTY(meta=(BindWidget))
    UImage* ItemImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Info")
    EAttachmentType SlotAttachmentType;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Info")
    FName SocketName;
    
    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

    UAceAttachmentItemObject* ItemObject;
    
private:
};
