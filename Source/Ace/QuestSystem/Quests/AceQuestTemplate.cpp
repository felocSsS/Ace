// Ace Game. All Rights Reserved.

#include "QuestSystem/Quests/AceQuestTemplate.h"
#include "QuestSystem/Objectives/AceObjectiveCollection.h"
#include "QuestSystem/Objectives/AceObjectiveReachDestination.h"

UAceObjectiveCollection* AAceQuestTemplate::ConstructRootObjectiveCollection()
{
    const auto RootObjective = NewObject<UAceObjectiveCollection>(this);

    if (RootObjective)
    {
        RootObjective->OrderRequired = true;
        RootObjective->SetObjectiveName(FText::FromName("QuestName"));
        return RootObjective;
    }

    return nullptr;
}

void AAceQuestTemplate::PopulateObjectives()
{
    const auto Task1 = NewObject<UAceObjectiveReachDestination>(this);
    const auto Task2 = NewObject<UAceObjectiveReachDestination>(this);

    if (Task1)
    {
        Task1->Destination = MegatonTrigger;
        Task1->SetObjectiveName(FText::FromName("Reach Megaton"));
        RootObjectiveCollection->AddObjective(Task1);
    }

    if (Task2)
    {
        Task2->Destination = ArchangeTrigger;
        Task2->SetObjectiveName(FText::FromName("Reach Archange"));
        RootObjectiveCollection->AddObjective(Task2);
    }
}
