// Ace Game. All Rights Reserved.


#include "Weapon/AceRifleWeapon.h"
#include "Curves/CurveVector.h"
#include "Components/TimelineComponent.h"

AAceRifleWeapon::AAceRifleWeapon()
{
    
}

void AAceRifleWeapon::BeginPlay()
{
    Super::BeginPlay();

    CurrentRecoilTime = 0.0f;
    FOnTimelineVector Update;
    Update.BindUFunction(this, "TimelineUpdate");
    TimeLine.AddInterpVector(RecoilCurve, Update);
}

void AAceRifleWeapon::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    TimeLine.TickTimeline(DeltaSeconds);
}

void AAceRifleWeapon::StartFire()
{
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AAceRifleWeapon::MakeShot, TimeBetweenShots, true);
    MakeShot();
    TimeLine.Play();
}

void AAceRifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    CurrentRecoilTime = 0.0f;
    TimeLine.Stop();
    TimeLine.SetNewTime(0.0f);
}

void AAceRifleWeapon::MakeShot()
{
    //CurrentRecoilTime += TimeBetweenShots;
    //AddRecoil();
}

void AAceRifleWeapon::AddRecoil()
{
    if (!RecoilCurve) return;
    
    const FVector RecoilVector = RecoilCurve->GetVectorValue(CurrentRecoilTime);
    const auto Controller = Cast<APlayerController>(GetController());
    if (!Controller) return;
    
    Controller->AddPitchInput(-RecoilVector.Y);
    Controller->AddYawInput(RecoilVector.X);
}

void AAceRifleWeapon::TimelineUpdate(FVector RecoilVector)
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
