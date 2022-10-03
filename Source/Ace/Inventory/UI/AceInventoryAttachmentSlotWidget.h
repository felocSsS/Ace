// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/AceBaseWidget.h"
#include "Weapon/Attachments/AceBaseWeaponAttachment.h"
#include "AceInventoryAttachmentSlotWidget.generated.h"

class UImage;
class UAceBaseItemObject;
class UAceAttachmentItemObject;

UCLASS()
class ACE_API UAceInventoryAttachmentSlotWidget : public UAceBaseWidget
{
	GENERATED_BODY()
	    
public:
    int32 WeaponIndex;
    
    void SetIconAndSpawn(UAceAttachmentItemObject* AttachemntItemObject);
    void SetIcon(UAceBaseItemObject* Attachemnt);
    void ClearSlot();
    
protected:
    UPROPERTY(meta=(BindWidget))
    UImage* ItemImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Info")
    EAttachmentType SlotAttachmentType;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Info")
    FName SocketName;
    
    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

    UAceBaseItemObject* ItemObject;
    
private:
};
