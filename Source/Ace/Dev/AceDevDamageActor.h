// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AceDevDamageActor.generated.h"

USceneComponent;

UCLASS()
class ACE_API AAceDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAceDevDamageActor();

public:	
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Dev")
    USceneComponent* SceneComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Dev")
    float Radius = 300.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Dev")
    FColor SphereColor = FColor::Red;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Dev")
    float Damage = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UDamageType> DamageType;

protected:

private:
    
};
