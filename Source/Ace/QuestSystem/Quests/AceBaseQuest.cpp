// Ace Game. All Rights Reserved.

#include "QuestSystem/Quests/AceBaseQuest.h"
#include "Components/BillboardComponent.h"
#include "QuestSystem/Objectives/AceObjectiveCollection.h"

AAceBaseQuest::AAceBaseQuest()
{
	PrimaryActorTick.bCanEverTick = false;

    Billboard = CreateDefaultSubobject<UBillboardComponent>("Billboard");
    SetRootComponent(Billboard);
}

UAceObjectiveCollection* AAceBaseQuest::GetRootObjectiveCollection() const
{
    return RootObjectiveCollection;
}

void AAceBaseQuest::BeginPlay()
{
	Super::BeginPlay();

    RootObjectiveCollection = ConstructRootObjectiveCollection();
    PopulateObjectives();
    RootObjectiveCollection->ActivateObjective();
}

UAceObjectiveCollection* AAceBaseQuest::ConstructRootObjectiveCollection()
{
    return nullptr;
}

void AAceBaseQuest::PopulateObjectives()
{
}
