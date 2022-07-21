// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AceBaseWeapon.generated.h"

UCLASS()
class ACE_API AAceBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	AAceBaseWeapon();

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USkeletalMeshComponent* WeaponMesh;
    
    virtual void StartFire();
    virtual void StopFire();
    virtual void MakeShot();
    virtual void AddRecoil();
    
protected:
	virtual void BeginPlay() override;

private:
};
