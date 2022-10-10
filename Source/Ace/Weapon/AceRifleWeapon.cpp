// Ace Game. All Rights Reserved.

#include "Weapon/AceRifleWeapon.h"
#include "Animation/AcePlayerAnimInstance.h"
#include "Attachments/AceBaseWeaponAttachment.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "Objects/WeaponItemObject/AceARItemObject.h"

void AAceRifleWeapon::BeginPlay()
{
    Super::BeginPlay();
    
    FOnTimelineVector Update;
    Update.BindUFunction(this, "TimelineUpdate");
    TimeLine.AddInterpVector(RecoilCurve, Update);
}

void AAceRifleWeapon::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    TimeLine.TickTimeline(DeltaSeconds);
    
    if(!Character)
    {
        Character = Cast<ACharacter>(GetOwner());
        if(Character)
            AnimInstance = Cast<UAcePlayerAnimInstance>(Character->GetMesh()->GetAnimInstance());   
    }
}

void AAceRifleWeapon::StartFire()
{
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AAceRifleWeapon::MakeShot, TimeBetweenShots, true);
    MakeShot();
    if (!IsAmmoEmpty() && !IsClipEmpty())
        TimeLine.Play();
}

void AAceRifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    TimeLine.Stop();
    TimeLine.SetNewTime(0.0f);
}

void AAceRifleWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty() || IsClipEmpty())
    {
        StopFire();
        return;
    }

    FVector TraceStart, TraceEnd, EditedDirection;
    if (!GetTraceData(TraceStart, TraceEnd, EditedDirection))
    {
        StopFire();
        return;
    }

    TArray<FHitResult> HitResults;
    MakeMultiHit(HitResults, TraceStart, TraceEnd);

    for (const FHitResult Hit: HitResults)
    {
        DrawDebugLine(GetWorld(), WeaponMesh->GetSocketLocation("Muzzle"), Hit.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
        if(Hit.bBlockingHit)
        {
            DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f); 
        }
    }

    if(AnimInstance)
    {
        AnimInstance->Fire();    
    }
    
    DecreaseAmmo();
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::SanitizeFloat(CurrentAmmo.Bullets));
}

void AAceRifleWeapon::UpdateItemObject()
{
    if (!ItemObject)
    {
        GetDefaultItemObject();
    }
    else
    {
        Cast<UAceARItemObject>(ItemObject)->CurrentAttachemntsItemObjects = CurrentAttachmentsItemObjects;
    }
}

bool AAceRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd, FVector& EditedDir) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;
    const auto HalfRand = FMath::DegreesToRadians(0.0f);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRand);
    EditedDir = ShootDirection;
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

void AAceRifleWeapon::GetDefaultItemObject()
{
    auto NewItemObject = NewObject<UAceARItemObject>(this);
    if (!NewItemObject) return;

    NewItemObject->SetClass(SpawnClass);
    NewItemObject->SetIcon(Icon);
    NewItemObject->SetName(ItemName);
    NewItemObject->IsASightAvailable = IsASightAvailable;
    NewItemObject->IsAGripAvailable = IsAGripAvailable;
    NewItemObject->IsASilencerAvailable = IsASilencerAvailable;
    NewItemObject->CurrentAttachemntsItemObjects = CurrentAttachmentsItemObjects;
    
    ItemObject = NewItemObject;
}

void AAceRifleWeapon::TimelineUpdate(const FVector RecoilVector) const
{
    const auto Controller = Cast<APlayerController>(GetController());
    if (!Controller) return;
    
    Controller->AddPitchInput(-RecoilVector.Y);
    Controller->AddYawInput(RecoilVector.X);
}

AController* AAceRifleWeapon::GetController() const
{
    const APawn* Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}