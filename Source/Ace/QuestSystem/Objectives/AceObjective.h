// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AceObjective.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCompleted, class UAceObjective*, Objective);

UCLASS()
class ACE_API UAceObjective : public UObject
{
	GENERATED_BODY()

public:
    virtual bool GetIsComplete() const;
    virtual void ActivateObjective();
    FText GetObjectiveName() const;

    void SetObjectiveName(FText Name);

    FOnCompleted OnCompletedDelegate;
    
protected:
    bool IsActive;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="QuestInfo")
    FText ObjectiveName;
    bool GetIsActive() const;
    
private:
    
};