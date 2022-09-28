// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Weapon/AceBaseWeapon.h"
#include "AceRifleWeapon.generated.h"

class UCurveVector;
class UAcePlayerAnimInstance;
class AAceBaseWeaponAttachment;

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
    virtual void UpdateItemObject() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd, FVector& EditedDir) const override;
    
    UPROPERTY(BlueprintReadOnly, Category="Anim")
    UAcePlayerAnimInstance* AnimInstance;
private:
    FTimerHandle ShotTimerHandle;
    FTimeline TimeLine;
    
    UFUNCTION()
    void TimelineUpdate(const FVector RecoilVector) const;

    virtual void GetDefaultItemObject() override;
    
    AController* GetController() const;

    ACharacter* Character;
};

