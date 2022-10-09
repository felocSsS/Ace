// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Objects/AceBaseItemObject.h"
#include "Weapon/Attachments/AceBaseWeaponAttachment.h"
#include "AceAttachmentItemObject.generated.h"

UCLASS()
class ACE_API UAceAttachmentItemObject : public UAceBaseItemObject
{
	GENERATED_BODY()

public:
    EAttachmentType AttachmentType;
    
protected:

private:
};
