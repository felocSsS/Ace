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
	AAcePlayerCharacter();
	
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void Tick(float DeltaSeconds) override;

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
    
    UPROPERTY(BlueprintReadOnly, Category="Anim")
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

    bool ItemDirty;
    
    AAceBaseInteractableItem* Item;
    AAceGameHUD* GameHUD;
};
