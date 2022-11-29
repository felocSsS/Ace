// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuestSystem/Objectives/AceObjective.h"
#include "AceObjectiveReachDestination.generated.h"

class ATriggerBase;

UCLASS()
class ACE_API UAceObjectiveReachDestination : public UAceObjective
{
	GENERATED_BODY()

public:
    bool ReachedDesination;

    virtual void ActivateObjective() override;
    virtual bool GetIsComplete() const override;

    ATriggerBase* Destination;
    
protected:
    
private:
    UFUNCTION()
    void OnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};