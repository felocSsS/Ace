// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AceBaseItem.h"
#include "AceBaseInteractableItem.generated.h"

class UBoxComponent;
class AAceBaseWeapon;

UCLASS()
class ACE_API AAceBaseInteractableItem : public AAceBaseItem
{
	GENERATED_BODY()

public:
    AAceBaseInteractableItem();
    
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Item")
    USkeletalMeshComponent* ItemMesh;
        
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Item")
    UBoxComponent* CollisionBox;
    
protected:
    virtual void BeginPlay() override;
    virtual void GetDefaultItemObject() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Info")
    TSubclassOf<AAceBaseWeapon> ItemClass;
    
private:
    
    
};
