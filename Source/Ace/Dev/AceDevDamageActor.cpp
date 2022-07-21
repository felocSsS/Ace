// Ace Game. All Rights Reserved.


#include "Dev/AceDevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

AAceDevDamageActor::AAceDevDamageActor()
{
	PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    SetRootComponent(SceneComponent);
}

void AAceDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(GetWorld())
    {
        DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);
        UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {}, this,
             nullptr, true);
    }
}

