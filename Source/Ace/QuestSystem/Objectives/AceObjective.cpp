// Ace Game. All Rights Reserved.

#include "QuestSystem/Objectives/AceObjective.h"

void UAceObjective::ActivateObjective()
{
    IsActive = true;
}

FText UAceObjective::GetObjectiveName() const
{
    return ObjectiveName;
}

void UAceObjective::SetObjectiveName(FText Name)
{
    ObjectiveName = Name;
}

bool UAceObjective::GetIsComplete() const
{
    return true;
}

bool UAceObjective::GetIsActive() const
{
    return IsActive;
}
