// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/AceBaseItem.h"
#include "AceBaseWeapon.generated.h"

class AAceSightAttachment;
class AAceSilencerAttachment;
class AAceGripAttachment;
class AAceBaseWeaponAttachment;

USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 Bullets;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 Clips;
};

USTRUCT(BlueprintType)
struct FAttachment
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachment")
    TSubclassOf<AAceSightAttachment> Sight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachment")
    TSubclassOf<AAceSilencerAttachment> Silencer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachment")
    TSubclassOf<AAceGripAttachment> Grip;
};

USTRUCT(BlueprintType)
struct FAttachmentsReferences
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachment")
    AAceSightAttachment* Sight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachment")
    AAceSilencerAttachment* Silencer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachment")
    AAceGripAttachment* Grip;
};

UCLASS()
class ACE_API AAceBaseWeapon : public AAceBaseItem
{
	GENERATED_BODY()
	
public:
	AAceBaseWeapon();

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Weapon")
    FAmmoData DefaultAmmo {30, 4} ;
    
    virtual void StartFire();
    virtual void StopFire();
    virtual void MakeShot();
    virtual void AddRecoil();

    void ChangeClip();
    void SpawnStartAttachment();
    
    FTransform GetSightTransform() const;
    FTransform GetGripTransform() const;

    bool IsAmmoEmpty() const;
    bool IsAmmoFull() const;
    bool CanReload() const;
    
    FAmmoData GetAmmoData() const { return CurrentAmmo; }
    
protected:
	virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Attachment")
    FAttachment StartAttachments;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Attachment")
    FAttachmentsReferences CurrentAttachments;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Weapon")
    float TraceMaxDistance = 15000.0f;

    void DecreaseAmmo();
    void MakeMultiHit(TArray<FHitResult>& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd, FVector& EditedDir) const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    bool IsClipEmpty() const;

    FAmmoData CurrentAmmo;
    
private:
    void AttachAttachmentToSocket(AAceBaseWeaponAttachment* Attachment, USceneComponent* SceneComponent, const FName SocketName);
};
