// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Attachments/AceBaseWeaponAttachment.h"
#include "AceSilencerAttachment.generated.h"


UCLASS()
class ACE_API AAceSilencerAttachment : public AAceBaseWeaponAttachment
{
	GENERATED_BODY()

public:

protected:
    virtual void BeginPlay() override;
    
private:
    virtual void GetDefaultItemObject() override;
	
};
