// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AceBaseItem.h"
#include "AceBaseItemObject.generated.h"

UCLASS(Blueprintable)
class ACE_API UAceBaseItemObject : public UObject
{
	GENERATED_BODY()

public:
    TSubclassOf<AAceBaseItem> ItemClass;
protected:

private:
};
