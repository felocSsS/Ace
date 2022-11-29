// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuestSystem/Objectives/AceObjective.h"
#include "AceObjectiveCollection.generated.h"

UCLASS()
class ACE_API UAceObjectiveCollection : public UAceObjective
{
	GENERATED_BODY()

public:
    virtual void ActivateObjective() override;
    bool OrderRequired;
    void AddObjective(UAceObjective* Objective);
    
protected:
    TArray<UAceObjective*> Objectives;

    virtual bool GetIsComplete() const override;
    
private:
    UAceObjective* FindNextIncompleteObjective();
    UFUNCTION()
    void OnObjectiveCompleted(UAceObjective* Objective);
    void NextObjective();
};