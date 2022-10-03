// Ace Game. All Rights Reserved.


#include "Components/AceHealthComponent.h"

UAceHealthComponent::UAceHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAceHealthComponent::BeginPlay()
{
	Super::BeginPlay();
    check(MaxHealth > 0);

    SetHealth(MaxHealth, MaxHealth); // TODO попробовать сделать перегрузку функцию

    AActor* ComponentOwner = GetOwner();

    if (ComponentOwner)
    {
        ComponentOwner->OnTakePointDamage.AddDynamic(this, &UAceHealthComponent::OnTakePointDamege);
        ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &UAceHealthComponent::OnRadialDamage);
    }
}

void UAceHealthComponent::SetHealth(float NewHealth, float HealthToClamp) // HealthToClamp - Здоровье, выше которого функция не прибавит
{
    const float NextHealth = FMath::Clamp(NewHealth, 0.0f, HealthToClamp);

    Health = NextHealth;
}

void UAceHealthComponent::HealthUpdate()
{
    if ((GetHealthPercent() < MaxHealthToHeal / 100) && !IsDead())
    {
        SetHealth(Health + HealModifier, MaxHealth);
    }
    else if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealthTimerHandle);
    }
}

float UAceHealthComponent::GetHealthPercent() const
{
    return Health / MaxHealth;
}

bool UAceHealthComponent::IsDead() const
{
    return FMath::IsNearlyZero(Health);
}

void UAceHealthComponent::OnTakePointDamege(AActor* DamagedActor, float Damage, AController* InstigatedBy,
                                            FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection,
                                            const UDamageType* DamageType, AActor* DamageCauser)
{
    const float FinalDamage = Damage;
    ApplyDamage(Damage, InstigatedBy);
}

void UAceHealthComponent::OnRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
    FVector Origin, FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
    ApplyDamage(Damage, InstigatedBy);
}

void UAceHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld()) return;

    SetHealth(Health - Damage, MaxHealth);
    
    if (IsDead())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealthTimerHandle);
    }
    else if (AutoHeal)
    {
        GetWorld()->GetTimerManager().SetTimer(HealthTimerHandle, this, &UAceHealthComponent::HealthUpdate, HealUpdateTime, true, HealDelay);
    }
}
