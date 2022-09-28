// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AceInventoryWidget.generated.h"

class UAceInventoryWeaponSlotWidget;

UCLASS()
class ACE_API UAceInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
     
public:
    
protected:
    UPROPERTY(meta=(BindWidget))
    UAceInventoryWeaponSlotWidget* WeaponSlotWidget1;

    UPROPERTY(meta=(BindWidget))
    UAceInventoryWeaponSlotWidget* WeaponSlotWidget2;

    UPROPERTY(meta=(BindWidget))
    UAceInventoryWeaponSlotWidget* WeaponSlotWidget3;
private:
    TArray<UAceInventoryWeaponSlotWidget*> Array { WeaponSlotWidget1, WeaponSlotWidget2, WeaponSlotWidget3};
};
