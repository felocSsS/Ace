// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AceInventoryAttachmentSlotWidget.generated.h"

class UImage;
class UAceBaseItemObject;

UCLASS()
class ACE_API UAceInventoryAttachmentSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	    
public:
    int32 WeaponIndex;
    
protected:
    UPROPERTY(meta=(BindWidget))
    UImage* ItemImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Info")
    TSubclassOf<UAceBaseItemObject> ItemClassOfThisSlot;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Info")
    FName SocketName;
    
    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
private:
};
