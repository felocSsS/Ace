// Ace Game. All Rights Reserved.

#include "Components/AceInventoryComponent.h"
#include "Objects/AceBaseItemObject.h"

UAceInventoryComponent::UAceInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAceInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UAceInventoryComponent::AddItem(UAceBaseItemObject* ItemObject)
{
    if (!ItemObject) return false;

    Items.Add(ItemObject);
    OnItemAdded.Broadcast(ItemObject);
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