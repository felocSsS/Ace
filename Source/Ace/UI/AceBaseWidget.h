// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AceBaseWidget.generated.h"

class AAcePlayerCharacter;
class AAceGameHUD;

UCLASS()
class ACE_API UAceBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:

protected:
    virtual void NativeOnInitialized() override;

    AAcePlayerCharacter* Character;
    APlayerController* CharacterController;
    AAceGameHUD* HUD;
    
private:
    
};
