// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AceBaseWeaponAttachment.generated.h"

UCLASS()
class ACE_API AAceBaseWeaponAttachment : public AActor
{
	GENERATED_BODY()
	
public:	
	AAceBaseWeaponAttachment();

public:
    UStaticMeshComponent* GetMesh() const { return AttachmentMesh; }
    
    FTransform GetAttachmentSocket(FName SocketName) const;
    
protected:
	virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category= "Attachment")
    UStaticMeshComponent* AttachmentMesh;
};
