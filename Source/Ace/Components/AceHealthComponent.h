// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AceHealthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACE_API UAceHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:	
    UAceHealthComponent();

public:	
    UFUNCTION(BlueprintCallable, Category="Health")
    bool IsDead() const;

    UFUNCTION(BlueprintCallable, Category="Health")
    float GetHealthPercent() const;
    
    float GetHealth() const { return Health; }
    float GetMaxHealth() const { return MaxHealth; }

    bool IsHealthFull() const { return FMath::IsNearlyEqual(Health, MaxHealth); }
    
protected:
	virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(ClampMin = "0.0", ClampMax = "1000.0"), Category="Health")
    float MaxHealth = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Heal")
    bool AutoHeal= false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Heal", meta = (EditCondition = "AutoHeal"))
    float HealUpdateTime = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Heal", meta = (EditCondition = "AutoHeal"))
    float HealModifier = 5.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealDelay = 3.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Heal", meta = (EditCondition = "AutoHeal"))
    float MaxHealthToHeal = 60.0f; 
    
private:
    float Health = 0.0f;

    FTimerHandle HealthTimerHandle;

    void HealthUpdate();
    void SetHealth(float NewHealth, float HealthToClamp);
    void ApplyDamage(float Damage, AController* InstigatedBy);

    UFUNCTION()
    void OnTakePointDamege(AActor* DamagedActor, float Damage, class AController* InstigatedBy,
                           FVector HitLocation, class UPrimitiveComponent*
                           FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType*
                           DamageType, AActor* DamageCauser);
    UFUNCTION()
    void OnRadialDamage(AActor* DamagedActor, float Damage,
                        const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo,
                        class AController* InstigatedBy, AActor* DamageCauser);
};
