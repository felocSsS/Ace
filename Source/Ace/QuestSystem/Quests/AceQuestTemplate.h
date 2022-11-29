// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuestSystem/Quests/AceBaseQuest.h"
#include "AceQuestTemplate.generated.h"

class ATriggerBase;

UCLASS()
class ACE_API AAceQuestTemplate : public AAceBaseQuest
{
	GENERATED_BODY()

public:

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Triggers")
    ATriggerBase* MegatonTrigger;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Triggers")
    ATriggerBase* ArchangeTrigger;
    
    virtual UAceObjectiveCollection* ConstructRootObjectiveCollection() override;
    virtual void PopulateObjectives() override;
private:
    
};