// Ace Game. All Rights Reserved.

#include "AceBaseItem.h"
#include "Components/AceInventoryComponent.h"
#include "Objects/AceBaseItemObject.h"
#include "Player/AcePlayerCharacter.h"

AAceBaseItem::AAceBaseItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAceBaseItem::BeginPlay()
{
	Super::BeginPlay();
    
    if (!ItemObject) GetDefaultItemObject(); //GetWorldTimerManager().SetTimerForNextTick(this, &AAceBaseItem::GetDefaultItemObject);
}

void AAceBaseItem::GetDefaultItemObject()
{
    GetWorldTimerManager().SetTimerForNextTick(this, &AAceBaseItem::AddItemObjectToInventory);
}

void AAceBaseItem::AddItemObjectToInventory()
{
    const AAcePlayerCharacter* Character = Cast<AAcePlayerCharacter>(GetOwner());
    if (!Character)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "NO");
        return;
    }
    
    Character->InventoryComponent->AddItem(ItemObject);
}