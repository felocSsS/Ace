// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/AceBaseInteractableItem.h"
#include "AceInteractableAttachment.generated.h"

UCLASS()
class ACE_API AAceInteractableAttachment : public AAceBaseInteractableItem
{
	GENERATED_BODY()

public:

protected:
    virtual void GetDefaultItemObject() override;
    
private:
    
};
