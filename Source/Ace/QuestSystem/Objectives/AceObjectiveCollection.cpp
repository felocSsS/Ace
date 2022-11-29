// Ace Game. All Rights Reserved.

#include "QuestSystem/Objectives/AceObjectiveCollection.h"

void UAceObjectiveCollection::ActivateObjective()
{
    Super::ActivateObjective();

    if (OrderRequired)
    {
        NextObjective();
    }
    else
    {
        for (const auto Objective : Objectives)
        {
            Objective->ActivateObjective();
        }
    }
}

bool UAceObjectiveCollection::GetIsComplete() const
{
    for (const auto Objective : Objectives)
    {
        if (!Objective->GetIsComplete())
            return false;
    }

    return true;
}

UAceObjective* UAceObjectiveCollection::FindNextIncompleteObjective()
{
    for (const auto Objective : Objectives)
    {
        if (!Objective->GetIsComplete())
            return Objective;
    }

    return nullptr;
}

void UAceObjectiveCollection::AddObjective(UAceObjective* Objective)
{
    if (!Objective) return;

    Objectives.Add(Objective);
}

void UAceObjectiveCollection::OnObjectiveCompleted(UAceObjective* Objective)
{
    Objective->OnCompletedDelegate.RemoveDynamic(this, &UAceObjectiveCollection::OnObjectiveCompleted);
    if (GetIsComplete())
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, "QuestComplete");  
    }
    else
    {
        NextObjective();
    }
}

void UAceObjectiveCollection::NextObjective()
{
    const auto NextObjective = FindNextIncompleteObjective();
    if (NextObjective)
    {
        NextObjective->ActivateObjective();
        NextObjective->OnCompletedDelegate.AddDynamic(this, &UAceObjectiveCollection::OnObjectiveCompleted);
    }
}
