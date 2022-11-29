// Ace Game. All Rights Reserved.

#include "QuestSystem/Objectives/AceObjectiveReachDestination.h"
#include "Engine/TriggerBase.h"
#include "Player/AcePlayerCharacter.h"

void UAceObjectiveReachDestination::ActivateObjective()
{
    Super::ActivateObjective();

    if (Destination)
    {
        Destination->OnActorBeginOverlap.AddDynamic(this, &UAceObjectiveReachDestination::OnActorBeginOverlap);
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, "ActivateObjective");   
    }
}

bool UAceObjectiveReachDestination::GetIsComplete() const
{
    return ReachedDesination;
}

void UAceObjectiveReachDestination::OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    const auto player = Cast<AAcePlayerCharacter>(OtherActor);
    if (player)
    {
        Destination->OnActorBeginOverlap.RemoveDynamic(this, &UAceObjectiveReachDestination::OnActorBeginOverlap);
        ReachedDesination = true;
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, "Trigger");
        OnCompletedDelegate.Broadcast(this);
    }
}
