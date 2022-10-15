// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/AceBaseCharacter.h"
#include "AcePlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractableItemChangeDelegate, bool, ShowWidget, FText, ItemName);

class UCameraComponent;
class UAcePlayerAnimInstance;
class USkeletalMeshComponent;
class UAceInventoryComponent;
class UAceBaseItemObject;
class AAceBaseInteractableItem;
class AAceGameHUD;

UCLASS()
class ACE_API AAcePlayerCharacter : public AAceBaseCharacter
{
	GENERATED_BODY()

public:
	AAcePlayerCharacter(const FObjectInitializer& ObjInit);
	
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void Tick(float DeltaSeconds) override;

    bool IsRunning() const;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USkeletalMeshComponent* ClientMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    UAceInventoryComponent* InventoryComponent;

    UPROPERTY(BlueprintAssignable, Category="Delegates")
    FOnInteractableItemChangeDelegate OnInteractableItemChange;

    float ADSAlpha;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Vars")
    float ForwardValue;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Vars")
    float RightValue;

protected:
    virtual void BeginPlay() override;
    virtual void OnGroundLanded(const FHitResult& Hit) override;
    
    UAcePlayerAnimInstance* AnimInstance;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
    void Aim();
    void ResetAim();
    void TryFindInteractableItem();
    void GetTraceData(FVector& TraceStart, FVector& TraceEnd);
    void PickUpItem();
    void OpenInventory();
    void AceJump();
    void StartRunning();
    void StopRunning();
    
    bool ItemDirty;
    bool WantsToRun;
    bool IsMovingForward;
    bool IsAiming;
    
    AAceBaseInteractableItem* Item;
    AAceGameHUD* GameHUD;
};
