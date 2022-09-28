// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Objects/AceBaseItemObject.h"
#include "Weapon/AceBaseWeapon.h"
#include "AceARItemObject.generated.h"

UCLASS()
class ACE_API UAceARItemObject : public UAceBaseItemObject
{
	GENERATED_BODY()

public:
    bool IsASightAvailable;
    bool IsASilencerAvailable;
    bool IsAGripAvailable;

    FAttachmentsReferences CurrentAttachemnts;
protected:
    
private:
    
};
