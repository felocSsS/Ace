// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AceInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAdded, class UAceBaseItemObject*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemDeleted, class UAceBaseItemObject*, Item);

class UAceBaseItemObject;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACE_API UAceInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAceInventoryComponent();

public:
    UPROPERTY(BlueprintAssignable)
    FOnItemAdded OnItemAdded;

    UPROPERTY(BlueprintAssignable)
    FOnItemDeleted OnItemDeleted;
    
    bool AddItem(UAceBaseItemObject* ItemObject);

    //test

    UFUNCTION(BlueprintCallable)
    void BPGetAllItems(TArray<UAceBaseItemObject*>& ArrayItems) const;
    
    //test
    
    TArray<UAceBaseItemObject*> GetAllItems() const;
    TArray<UAceBaseItemObject*> GetItemsOfClass(const TSubclassOf<UAceBaseItemObject> Class) const;
    
protected:
	virtual void BeginPlay() override;
    
    UPROPERTY(EditDefaultsOnly, Category="Item Info")
    UTexture* Icon;
    
    UPROPERTY(EditDefaultsOnly, Category="Item Info")
    FName Name;
    
private:
    TArray<UAceBaseItemObject*> Items;
};
