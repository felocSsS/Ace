// Ace Game. All Rights Reserved.


#include "Weapon/AceBaseWeapon.h"
#include "Player/AceBaseCharacter.h"
#include "Attachments/AceBaseWeaponAttachment.h"
#include "Components/AceInventoryComponent.h"
#include "Components/AceWeaponComponent.h"
#include "Player/AcePlayerCharacter.h"

AAceBaseWeapon::AAceBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

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
    const AAcePlayerCharacter* Character = Cast<AAcePlayerCharacter>(GetOwner());
    if (!GetWorld() && !WeaponMesh && !Character) return;

    const auto SpawnedSight = GetWorld()->SpawnActor<AAceBaseWeaponAttachment>(Sight);
    const auto SpawnedSilencer = GetWorld()->SpawnActor<AAceBaseWeaponAttachment>(Silencer);
    const auto SpawnedGrip = GetWorld()->SpawnActor<AAceBaseWeaponAttachment>(Grip);
    
    if (SpawnedSight)
    {
        AttachAttachmentToSocket(SpawnedSight, WeaponMesh, "Sight");
        SpawnedSight->SetOwner(GetOwner());
        CurrentAttachments.Sight = Cast<AAceBaseWeaponAttachment>(SpawnedSight);
        Character->InventoryComponent->AddItem(SpawnedSight->GetItemObject());
    }

    if (SpawnedSilencer)
    {
        AttachAttachmentToSocket(SpawnedSilencer, WeaponMesh, "Silencer");
        SpawnedSilencer->SetOwner(GetOwner());
        CurrentAttachments.Silencer = Cast<AAceBaseWeaponAttachment>(SpawnedSilencer);
        Character->InventoryComponent->AddItem(SpawnedSilencer->GetItemObject()); 
    }
    
    if (SpawnedGrip)
    {
        AttachAttachmentToSocket(SpawnedGrip, WeaponMesh, "Grip");
        SpawnedGrip->SetOwner(GetOwner());
        CurrentAttachments.Grip = Cast<AAceBaseWeaponAttachment>(SpawnedGrip);
        Character->InventoryComponent->AddItem(SpawnedGrip->GetItemObject()); 
    }
}

void AAceBaseWeapon::SpawnAttachment(TSubclassOf<AAceBaseItem> Class, FName SocketName)
{
    const AAcePlayerCharacter* Character = Cast<AAcePlayerCharacter>(GetOwner());
    if (!Character) return;
    
    const auto Attachement = GetWorld()->SpawnActor<AAceBaseWeaponAttachment>(Class);
    if (!Attachement) return;

    AttachAttachmentToSocket(Attachement, WeaponMesh, SocketName);
    Attachement->SetOwner(GetOwner());

    if (Attachement->AttachmentType == EAttachmentType::Sight)
        CurrentAttachments.Sight = Attachement;

    if (Attachement->AttachmentType == EAttachmentType::Grip)
        CurrentAttachments.Grip = Attachement;

    if (Attachement->AttachmentType == EAttachmentType::Silencer)
        CurrentAttachments.Silencer = Attachement;

    Character->WeaponComponent->UpdateWeaponInfo();
}

void AAceBaseWeapon::AddRecoil()
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
    const auto AceCharacter = Cast<AAceBaseCharacter>(GetOwner());
    if (!AceCharacter) return false;

    if (AceCharacter->IsPlayerControlled())
    {
        const auto Controller = AceCharacter->GetController<APlayerController>();
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
    return !CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool AAceBaseWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;   
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






