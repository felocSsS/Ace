// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AceInventoryComponent.generated.h"

class UAceBaseItemObject;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACE_API UAceInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAceInventoryComponent();

public:
    bool AddItem(UAceBaseItemObject* ItemObject);
    
    TArray<UAceBaseItemObject*> GetAllItems() const;
    TArray<UAceBaseItemObject*> GetItemsOfClass(const TSubclassOf<UAceBaseItemObject> Class) const;
    
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
protected:
	virtual void BeginPlay() override;
    
private:
    TArray<UAceBaseItemObject*> Items;
};
