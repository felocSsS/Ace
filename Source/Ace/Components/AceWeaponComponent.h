// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AceWeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCurrentWeaponChangedDelegate, class AAceBaseWeapon*, CurrentWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateWeaponInfoDelegate);

class AAceBaseWeapon;
class AAceBaseItem;

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
    UPROPERTY(BlueprintAssignable, Category="Weapon")
    FCurrentWeaponChangedDelegate CurrentWeaponChangedDelegate;

    UPROPERTY(BlueprintAssignable, Category="Weapon")
    FUpdateWeaponInfoDelegate UpdateWeaponInfoDelegate;

    void StartFire();
    void StopFire();
    void Reload();
    virtual void NextWeapon();
    void EquipWeapon(int32 WeaponIndex);
    void AddWeapon(TSubclassOf<AAceBaseItem> Item, int32 AtIndex);
    void UpdateWeaponInfo() const { return UpdateWeaponInfoDelegate.Broadcast(); } 
    AAceBaseWeapon* GetWeaponAtIndex(int32 Index);
    
protected:
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
    AAceBaseWeapon* CurrentWeapon;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    TArray<FWeaponData> StartWeapons;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon")
    TArray<AAceBaseWeapon*> Weapons;

    int32 CurrentWeaponIndex;

    bool CanEquip() const;
    bool CanFire() const;
    
private:
    void SpawnStartWeapons();
    void ChangeClip();
    void AttachWeaponToSocket(AAceBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName SocketName);

    bool CanReload() const;
};
