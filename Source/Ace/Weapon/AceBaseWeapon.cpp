// Ace Game. All Rights Reserved.


#include "Weapon/AceBaseWeapon.h"
#include "Player/AceBaseCharacter.h"
#include "Attachments/AceBaseWeaponAttachment.h"
#include "Components/AceWeaponComponent.h"
#include "Items/Objects/AceBaseItemObject.h"
#include "Items/Objects/WeaponItemObject/AceARItemObject.h"
#include "Player/AcePlayerCharacter.h"

AAceBaseWeapon::AAceBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    WeaponMesh->SetupAttachment(RootComponent);
}

void AAceBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
    
    CurrentAmmo = DefaultAmmo;
}

void AAceBaseWeapon::StartFire()
{
}

void AAceBaseWeapon::StopFire()
{
}

void AAceBaseWeapon::MakeShot()
{
}

void AAceBaseWeapon::SpawnStartAttachment()
{
    const AAcePlayerCharacter* Character = GetAceCharacter();
    
    if (!GetWorld() && !WeaponMesh && !Character) return;

    if (Sight)
    {
        const auto SpawnedSight = GetWorld()->SpawnActor<AAceBaseWeaponAttachment>(Sight);
        AttachAttachmentToSocket(SpawnedSight, WeaponMesh, "Sight");
        SpawnedSight->SetOwner(GetOwner());
        CurrentAttachments.Sight = Cast<AAceBaseWeaponAttachment>(SpawnedSight);
        CurrentAttachmentsItemObjects.Sight = Cast<UAceAttachmentItemObject>(SpawnedSight->GetItemObject());
        //Character->InventoryComponent->AddItem(SpawnedSight->GetItemObject());
    }
    
    if (Silencer)
    {
        const auto SpawnedSilencer = GetWorld()->SpawnActor<AAceBaseWeaponAttachment>(Silencer);
        AttachAttachmentToSocket(SpawnedSilencer, WeaponMesh, "Silencer");
        SpawnedSilencer->SetOwner(GetOwner());
        CurrentAttachments.Silencer = Cast<AAceBaseWeaponAttachment>(SpawnedSilencer);
        CurrentAttachmentsItemObjects.Silencer = Cast<UAceAttachmentItemObject>(SpawnedSilencer->GetItemObject());
        //Character->InventoryComponent->AddItem(SpawnedSilencer->GetItemObject()); 
    }
    
    if (Grip)
    {
        const auto SpawnedGrip = GetWorld()->SpawnActor<AAceBaseWeaponAttachment>(Grip);
        AttachAttachmentToSocket(SpawnedGrip, WeaponMesh, "Grip");
        SpawnedGrip->SetOwner(GetOwner());
        CurrentAttachments.Grip = Cast<AAceBaseWeaponAttachment>(SpawnedGrip);
        CurrentAttachmentsItemObjects.Grip = Cast<UAceAttachmentItemObject>(SpawnedGrip->GetItemObject());
        //Character->InventoryComponent->AddItem(SpawnedGrip->GetItemObject()); 
    }

    UpdateItemObject();
}

void AAceBaseWeapon::SpawnAttachment(TSubclassOf<AAceBaseItem> Class, FName SocketName)
{
    if (!GetOwner() || !Class) return;
    const AAcePlayerCharacter* Character = GetAceCharacter();
    if (!Character) return;
    
    const auto Attachement = GetWorld()->SpawnActor<AAceBaseWeaponAttachment>(Class);
    if (!Attachement) return;

    AttachAttachmentToSocket(Attachement, WeaponMesh, SocketName);
    Attachement->SetOwner(GetOwner());

    if (Attachement->AttachmentType == EAttachmentType::Sight)
    {
        CurrentAttachments.Sight = Attachement;
        CurrentAttachmentsItemObjects.Sight = Cast<UAceAttachmentItemObject>(Attachement->GetItemObject());
    }

    if (Attachement->AttachmentType == EAttachmentType::Grip)
    {
        CurrentAttachments.Grip = Attachement;
        CurrentAttachmentsItemObjects.Grip = Cast<UAceAttachmentItemObject>(Attachement->GetItemObject());
    }

    if (Attachement->AttachmentType == EAttachmentType::Silencer)
    {
        CurrentAttachments.Silencer = Attachement;
        CurrentAttachmentsItemObjects.Silencer = Cast<UAceAttachmentItemObject>(Attachement->GetItemObject());
    }

    Character->WeaponComponent->UpdateWeaponInfo();
}

void AAceBaseWeapon::DestroyAttachment(UAceAttachmentItemObject* AttachmentItemObject)
{
    if (!AttachmentItemObject) return;

    const AAcePlayerCharacter* Character = GetAceCharacter();
    if (!Character) return;
    
    switch (AttachmentItemObject->AttachmentType)
    {
    case EAttachmentType::Grip:
        CurrentAttachments.Grip->Destroy();
        CurrentAttachments.Grip = nullptr;
        CurrentAttachmentsItemObjects.Grip = nullptr;
        break;

    case EAttachmentType::Sight:
        CurrentAttachments.Sight->Destroy();
        CurrentAttachments.Sight = nullptr;
        CurrentAttachmentsItemObjects.Sight = nullptr;
        break;

    case EAttachmentType::Silencer:
        CurrentAttachments.Silencer->Destroy();
        CurrentAttachments.Silencer = nullptr;
        CurrentAttachmentsItemObjects.Silencer = nullptr;
        break;
    }
    
    Character->WeaponComponent->UpdateWeaponInfo();
}

void AAceBaseWeapon::SpawnAttachmentsFromItemObject(FAttachmentsItemObjects Attachments)
{
    const AAcePlayerCharacter* Character = GetAceCharacter();
    if (!Character) return;
    
    if (Attachments.Sight)
    {
        const auto SpawnedSight = GetWorld()->SpawnActor<AAceBaseWeaponAttachment>(Attachments.Sight->GetObjectClass());
        AttachAttachmentToSocket(SpawnedSight, WeaponMesh, "Sight");
        SpawnedSight->SetOwner(GetOwner());
        CurrentAttachments.Sight = Cast<AAceBaseWeaponAttachment>(SpawnedSight);
        CurrentAttachmentsItemObjects.Sight = Attachments.Sight;
    }
    
    if (Attachments.Silencer)
    {
        const auto SpawnedSilencer = GetWorld()->SpawnActor<AAceBaseWeaponAttachment>(Attachments.Silencer->GetObjectClass());
        AttachAttachmentToSocket(SpawnedSilencer, WeaponMesh, "Silencer");
        SpawnedSilencer->SetOwner(GetOwner());
        CurrentAttachments.Silencer = Cast<AAceBaseWeaponAttachment>(SpawnedSilencer);
        CurrentAttachmentsItemObjects.Silencer = Attachments.Silencer;
    }
    
    if (Attachments.Grip)
    {
        const auto SpawnedGrip = GetWorld()->SpawnActor<AAceBaseWeaponAttachment>(Attachments.Grip->GetObjectClass());
        AttachAttachmentToSocket(SpawnedGrip, WeaponMesh, "Grip");
        SpawnedGrip->SetOwner(GetOwner());
        CurrentAttachments.Grip = Cast<AAceBaseWeaponAttachment>(SpawnedGrip);
        CurrentAttachmentsItemObjects.Grip = Attachments.Grip;
    }
    
    Character->WeaponComponent->UpdateWeaponInfo();
}

void AAceBaseWeapon::DestroyWeapon()
{
    if(CurrentAttachments.Sight)
        CurrentAttachments.Sight->Destroy();

    if(CurrentAttachments.Silencer)
        CurrentAttachments.Silencer->Destroy();

    if(CurrentAttachments.Grip)
        CurrentAttachments.Grip->Destroy();

    Destroy();
}

void AAceBaseWeapon::AddRecoil()
{
}

void AAceBaseWeapon::UpdateItemObject()
{
}

void AAceBaseWeapon::DecreaseAmmo()
{
    if (CurrentAmmo.Bullets == 0) return;

    CurrentAmmo.Bullets--;

    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        StopFire();
    }
}

void AAceBaseWeapon::MakeMultiHit(TArray<FHitResult>& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
    if(!GetWorld()) return;

    FCollisionObjectQueryParams CollisionObjectTypes;
    CollisionObjectTypes.AddObjectTypesToQuery(ECollisionChannel::ECC_PhysicsBody);
    CollisionObjectTypes.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
    CollisionObjectTypes.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
    
    FCollisionQueryParams CollisionParam;
    CollisionParam.AddIgnoredActor(GetOwner());
    CollisionParam.AddIgnoredActor(this);
    CollisionParam.bReturnPhysicalMaterial = true;

    GetWorld()->LineTraceMultiByObjectType(HitResult, TraceStart, TraceEnd, CollisionObjectTypes, CollisionParam);
}

bool AAceBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd, FVector& EditedDir) const
{
    FVector ViewLocation; 
    FRotator ViewRotation; 
    if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    EditedDir = ShootDirection;
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

bool AAceBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const AAcePlayerCharacter* Character = Cast<AAcePlayerCharacter>(GetOwner());
    if (!Character) return false;

    if (Character->IsPlayerControlled())
    {
        const auto Controller = Character->GetController<APlayerController>();
        if (!Controller) return false;

        Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    }
    else
    {
        ViewLocation = WeaponMesh->GetSocketLocation("Muzzle");
        ViewRotation = WeaponMesh->GetSocketRotation("Muzzle");
    }

    return true;
}

void AAceBaseWeapon::ChangeClip()
{
    if (CurrentAmmo.Clips == 0) return;
    CurrentAmmo.Clips -= 1;
    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
}

FTransform AAceBaseWeapon::GetSightTransform() const
{
    if (CurrentAttachments.Sight != nullptr)
        return CurrentAttachments.Sight->GetAttachmentSocket("Aim");
    else if (WeaponMesh)
        return WeaponMesh->GetSocketTransform("Aim");

    return FTransform();
}

FTransform AAceBaseWeapon::GetGripTransform() const
{
    if (CurrentAttachments.Grip != nullptr)
        return CurrentAttachments.Grip->GetAttachmentSocket("Grip");
    else if (WeaponMesh)
        return WeaponMesh->GetSocketTransform("l_hand_socket");
    
    return FTransform();
}

bool AAceBaseWeapon::IsAmmoEmpty() const
{
    return CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool AAceBaseWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;   
}

AAcePlayerCharacter* AAceBaseWeapon::GetAceCharacter()
{
    AAcePlayerCharacter* Character = Cast<AAcePlayerCharacter>(GetOwner());
    
    if (Character)
        return Character;
    else
        return nullptr;
}

void AAceBaseWeapon::AttachAttachmentToSocket(AAceBaseWeaponAttachment* Attachment, USceneComponent* SceneComponent,
                                              const FName SocketName)
{
    if (!Attachment || !SceneComponent) return;

    const FAttachmentTransformRules AttachmentsRoles(EAttachmentRule::KeepRelative, false);
    Attachment->AttachToComponent(SceneComponent, AttachmentsRoles, SocketName); 
}

bool AAceBaseWeapon::IsAmmoFull() const
{
    return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

bool AAceBaseWeapon::CanReload() const
{
    return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}