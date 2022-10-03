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
    UStaticMeshComponent* ItemMesh;
        
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Item")
    UBoxComponent* CollisionBox;
    
protected:
    virtual void GetDefaultItemObject() override;

private:
    
};
