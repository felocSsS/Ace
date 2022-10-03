// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/AceBaseWidget.h"
#include "AceInventoryWidget.generated.h"

class UAceInventoryWeaponSlotWidget;
class UAceInventoryGridWidget;

UCLASS()
class ACE_API UAceInventoryWidget : public UAceBaseWidget
{
	GENERATED_BODY()
     
public:
    UPROPERTY(meta=(BindWidget))
    UAceInventoryGridWidget* InventoryGrid;
    
protected:
    UPROPERTY(meta=(BindWidget))
    UAceInventoryWeaponSlotWidget* WeaponSlotWidget1;

    UPROPERTY(meta=(BindWidget))
    UAceInventoryWeaponSlotWidget* WeaponSlotWidget2;

    UPROPERTY(meta=(BindWidget))
    UAceInventoryWeaponSlotWidget* WeaponSlotWidget3;

private:
    
};
