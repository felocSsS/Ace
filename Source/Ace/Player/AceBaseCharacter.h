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
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    UAceWeaponComponent* WeaponComponent;
    
    float GetCharacterVelocity() const;
    float GetMovementDirection() const;
	
protected:
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    UAceHealthComponent* HealthComponent;

    UFUNCTION()
    virtual void OnGroundLanded(const FHitResult& Hit);
    
private:
    
};
