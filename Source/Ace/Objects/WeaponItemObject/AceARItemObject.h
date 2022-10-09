// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Attachment/AceAttachmentItemObject.h"
#include "Objects/AceBaseItemObject.h"
#include "AceARItemObject.generated.h"

USTRUCT(BlueprintType)
struct FAttachmentsItemObjects
{
    GENERATED_USTRUCT_BODY()
    
    UAceAttachmentItemObject* Sight;
    
    UAceAttachmentItemObject* Silencer;
    
    UAceAttachmentItemObject* Grip;
};

UCLASS()
class ACE_API UAceARItemObject : public UAceBaseItemObject
{
	GENERATED_BODY()

public:
    bool IsASightAvailable;
    bool IsASilencerAvailable;
    bool IsAGripAvailable;

    FAttachmentsItemObjects CurrentAttachemntsItemObjects;
    
protected:
    
private:
    
};
