// Ace Game. All Rights Reserved.

#include "Weapon/Attachments/AceBaseWeaponAttachment.h"
#include "Components/StaticMeshComponent.h"

AAceBaseWeaponAttachment::AAceBaseWeaponAttachment()
{
	PrimaryActorTick.bCanEverTick = true;

    AttachmentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AttachmentMesh"));
    AttachmentMesh->SetupAttachment(RootComponent);
}

void AAceBaseWeaponAttachment::BeginPlay()
{
	Super::BeginPlay();
	
	    
	
}

FTransform AAceBaseWeaponAttachment::GetAttachmentSocket(FName SocketName) const
{
    if (!AttachmentMesh) return FTransform();

    return AttachmentMesh->GetSocketTransform(SocketName);
}