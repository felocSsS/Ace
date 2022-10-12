// Ace Game. All Rights Reserved.

#include "AceBaseItem.h"
#include "Objects/AceBaseItemObject.h"
#include "Player/AcePlayerCharacter.h"

AAceBaseItem::AAceBaseItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAceBaseItem::BeginPlay()
{
	Super::BeginPlay();
    
    if (!ItemObject) GetDefaultItemObject(); 
}

void AAceBaseItem::GetDefaultItemObject()
{
    ItemObject = NewObject<UAceBaseItemObject>(this);
}

UAceBaseItemObject* AAceBaseItem::GetItemObject() const
{
    if (ItemObject)
        return ItemObject;
    else
        return nullptr;
}

FText AAceBaseItem::GetItemName() const
{
    return ItemName;
}