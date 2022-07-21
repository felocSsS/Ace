// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AceBaseCharacter.generated.h"

class UAceWeaponComponent;
class UAceHealthComponent;

UCLASS()
class ACE_API AAceBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAceBaseCharacter();

public:	
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category="Movement")
    float GetCharacterVelocity() const;

    UFUNCTION(BlueprintCallable, Category="Movement")
    float GetMovementDirection() const;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UAceWeaponComponent* WeaponComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    UAceHealthComponent* HealthComponent;

private:
	
};
