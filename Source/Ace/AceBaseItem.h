// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AceBaseItem.generated.h"

class UAceBaseItemObject;

UCLASS()
class ACE_API AAceBaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AAceBaseItem();

public:	
    
protected:
	virtual void BeginPlay() override;
    virtual void GetDefaultItemObject();
    virtual void AddItemObjectToInventory();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Info")
    UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Info")
    FText Name;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UAceBaseItemObject* ItemObject;
    
private:
    
};
