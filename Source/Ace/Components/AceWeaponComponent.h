// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AceWeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCurrentWeaponChangedDelegate, class AAceBaseWeapon*, CurrentWeapon);

class AAceBaseWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    TSubclassOf<AAceBaseWeapon> WeaponClass;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACE_API UAceWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAceWeaponComponent();

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
    AAceBaseWeapon* CurrentWeapon;

    UPROPERTY(BlueprintAssignable, Category="Weapon")
    FCurrentWeaponChangedDelegate CurrentWeaponChangedDelegate;

    void StartFire();
    void StopFire();
    virtual void NextWeapon();
    
protected:
	virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    TArray<FWeaponData> StartWeapons;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
    TArray<AAceBaseWeapon*> Weapons;

    void EquipWeapon(int32 WeaponIndex);

    int32 CurrentWeaponIndex;

    bool CanEquip() const;
    bool CanFire() const;
    
private:
    void SpawnWeapons();
    void AttachWeaponToSocket(AAceBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName SocketName);
};
