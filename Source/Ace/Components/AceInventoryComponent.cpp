// Ace Game. All Rights Reserved.

#include "Components/AceInventoryComponent.h"
#include "Objects/AceBaseItemObject.h"

UAceInventoryComponent::UAceInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAceInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UAceInventoryComponent::AddItem(UAceBaseItemObject* ItemObject)
{
    if (!ItemObject) return false;

    Items.Add(ItemObject);
    return true;
}

void UAceInventoryComponent::BPGetAllItems(TArray<UAceBaseItemObject*>& ArrayItems) const
{
    ArrayItems = Items;
}

TArray<UAceBaseItemObject*> UAceInventoryComponent::GetAllItems() const
{
    return Items;
}

TArray<UAceBaseItemObject*> UAceInventoryComponent::GetItemsOfClass(const TSubclassOf<UAceBaseItemObject> Class) const
{
    TArray<UAceBaseItemObject*> ArrayItemsOfClass;
    for (const auto Item : Items)
    {
        if (Item->IsA(Class)) ArrayItemsOfClass.Add(Item);
    }

    return ArrayItemsOfClass;
}

void UAceInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    /*for (const auto item : Items)
    {
        GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Black, item->GetName());
    }*/
}

