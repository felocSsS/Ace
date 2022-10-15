// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AceCharacterMovementComponent.generated.h"

UCLASS()
class ACE_API UAceCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
    virtual float GetMaxSpeed() const override;
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement", meta=(ClampMin="1.2", ClampMax="2.0"))
    float RunModifier;
    
private:
};
