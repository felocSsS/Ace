// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/AceBaseInteractableItem.h"
#include "AceInteractableRifle.generated.h"

UCLASS()
class ACE_API AAceInteractableRifle : public AAceBaseInteractableItem
{
	GENERATED_BODY()

public:

protected:
    virtual void GetDefaultItemObject() override;
    
private:
    
};
