// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Objects/AceBaseItemObject.h"
#include "AceGameHUD.generated.h"

class UAcePickUpMessageWidget;
class UAceInventoryWidget;
class AAcePlayerCharacter;

UCLASS()
class ACE_API AAceGameHUD : public AHUD
{
	GENERATED_BODY()

public:
    void ToggleInventory();
    
protected:
    virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PickUpMessageWidgetClass;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UAceInventoryWidget> InventoryWidgetClass;

    UAcePickUpMessageWidget* PickUpMessageWidget;

    UFUNCTION()
    void OnInteractableItemChange(bool ShowWidget, FText ItemName);
    
private:
    UAceInventoryWidget* InventoryWidget;
    AAcePlayerCharacter* Character;
    APlayerController* CharacterContoller;
};
