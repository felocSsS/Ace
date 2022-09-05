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

    //test

    UFUNCTION(BlueprintCallable)
    void BPGetAllItems(TArray<UAceBaseItemObject*>& ArrayItems) const;
    
    //test
    
    TArray<UAceBaseItemObject*> GetAllItems() const;
    TArray<UAceBaseItemObject*> GetItemsOfClass(const TSubclassOf<UAceBaseItemObject> Class) const;
    
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
protected:
	virtual void BeginPlay() override;
    
    UPROPERTY(EditDefaultsOnly, Category="Item Info")
    UTexture* Icon;
    
    UPROPERTY(EditDefaultsOnly, Category="Item Info")
    FName Name;
    
private:
    TArray<UAceBaseItemObject*> Items;
};
