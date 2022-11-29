// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AceBaseQuest.generated.h"

class UAceObjectiveCollection;

UCLASS()
class ACE_API AAceBaseQuest : public AActor
{
	GENERATED_BODY()
	
public:	
	AAceBaseQuest();
    UAceObjectiveCollection* GetRootObjectiveCollection() const;
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UBillboardComponent* Billboard;
    
    UAceObjectiveCollection* RootObjectiveCollection;
    
	virtual void BeginPlay() override;
    virtual UAceObjectiveCollection* ConstructRootObjectiveCollection();
    virtual void PopulateObjectives();
    
private:
    
};