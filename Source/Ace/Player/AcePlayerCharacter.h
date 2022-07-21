// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/AceBaseCharacter.h"
#include "AcePlayerCharacter.generated.h"

class UCameraComponent;
class UAcePlayerAnimInstance;
class USkeletalMeshComponent;

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

    float ADSAlpha;

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
