// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AceGameHUD.generated.h"

class UAcePickUpMessageWidget;

UCLASS()
class ACE_API AAceGameHUD : public AHUD
{
	GENERATED_BODY()

public:
    
protected:
    virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PickUpMessageWidgetClass;

    UAcePickUpMessageWidget* PickUpMessageWidget;

    UFUNCTION()
    void OnInteractableItemChange(bool ShowWidget, FText ItemName);
private:
    
};
