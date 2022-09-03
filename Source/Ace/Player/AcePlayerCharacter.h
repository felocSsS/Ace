// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/AceBaseCharacter.h"
#include "AcePlayerCharacter.generated.h"

class UCameraComponent;
class UAcePlayerAnimInstance;
class USkeletalMeshComponent;
class UAceInventoryComponent;

UCLASS()
class ACE_API AAcePlayerCharacter : public AAceBaseCharacter
{
	GENERATED_BODY()

public:
	AAcePlayerCharacter();
	
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USkeletalMeshComponent* ClientMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    UAceInventoryComponent* InventoryComponent;

    float ADSAlpha;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Vars")
    float ForwardValue;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Vars")
    float RightValue;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadOnly, Category="Anim")
    UAcePlayerAnimInstance* AnimInstance;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
    void Aim();
    void ResetAim();
};
