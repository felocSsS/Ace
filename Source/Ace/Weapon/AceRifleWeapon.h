// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Weapon/AceBaseWeapon.h"
#include "AceRifleWeapon.generated.h"

class UCurveVector;

UCLASS()
class ACE_API AAceRifleWeapon : public AAceBaseWeapon
{
	GENERATED_BODY()

public:
    AAceRifleWeapon();
    
public:
    virtual void StartFire() override;
    virtual void StopFire() override;
    virtual void Tick(float DeltaSeconds) override;
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    float TimeBetweenShots = 0.085f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    UCurveVector* RecoilCurve;
    
    virtual void BeginPlay() override;
    virtual void MakeShot() override;
    virtual void AddRecoil() override;

    float CurrentRecoilTime = 0.0f;
private:
    FTimerHandle ShotTimerHandle;
    FTimeline TimeLine;

    UFUNCTION()
    void TimelineUpdate(FVector RecoilVector);

    
    
    AController* GetController() const;
};
