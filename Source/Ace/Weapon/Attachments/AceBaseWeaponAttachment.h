// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/AceBaseItem.h"
#include "AceBaseWeaponAttachment.generated.h"

UENUM(BlueprintType)
enum class EAttachmentType : uint8
{
    Sight,
    Silencer,
    Grip
};

UCLASS()
class ACE_API AAceBaseWeaponAttachment : public AAceBaseItem
{
	GENERATED_BODY()
	
public:	
	AAceBaseWeaponAttachment();

public:
    UStaticMeshComponent* GetMesh() const { return AttachmentMesh; }
    
    FTransform GetAttachmentSocket(FName SocketName) const;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Info")
    EAttachmentType AttachmentType;
    
protected:
    virtual void GetDefaultItemObject() override;

private:
    UPROPERTY(EditAnywhere, Category= "Attachment")
    UStaticMeshComponent* AttachmentMesh;
};
