// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/TimelineComponent.h"
#include "AcePlayerAnimInstance.generated.h"

class AAcePlayerCharacter;
class AAceBaseWeapon;
class UAceWeaponComponent;
class UCurveVector;

UCLASS()
class ACE_API UAcePlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, Category="Recoil")
    FTransform RecoilTransform;

    void Fire();
    void StartJump();
    void FinishJump();
    
    float MoveRightValue;
    float MoveForwardValue;
    float ShakingModifier = 1.0f;

    bool bIsMovingRight = false;
    bool bIsMovingForward = false;
    
    FTransform FinalRecoilTransform;
    
protected:
    virtual void NativeBeginPlay() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    UFUNCTION()
    virtual void WeaponChanged(AAceBaseWeapon* NewWeapon);

    UFUNCTION()
    void UpdateInfo();

    UPROPERTY(BlueprintReadOnly, Category="Character")
    AAcePlayerCharacter* Character;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Anim")
    AAceBaseWeapon* CurrentWeapon;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anim")
    float CharacterVelocity;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anim")
    float Direction;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anim")
    float ADSAlpha;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anim")
    FRotator AimOffsetRotation;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anim")
    FRotator FinalTurnRotation;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Anim")
    FTransform RelativeCameraTransform;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Anim")
    FTransform LeftHandTransform;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Anim")
    FTransform RelativeHandTransform;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Anim")
    FTransform SidesWeaponSway;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Anim")
    FTransform MoveInSidesSway;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Anim")
    FVector WalkSwayLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Anim")
    FTransform JumpTransform;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Anim")
    UCurveVector* WalkCurve;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Anim")
    UCurveVector* MoveInSidesCurve;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Anim")
    UCurveVector* JumpStartCurve;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Anim")
    UCurveVector* JumpEndCurve;
    
    UAceWeaponComponent* WeaponComponent;

    APlayerController* PlayerController;

    float JumpPosition;
    float Test;
    
    FRotator ActualRotation;
    FRotator OldTurnRotation;
    FRotator TurnRotation;
    
private:
    void SetCharacterVars();
    void SetAimOffset();
    void SetRelativeCameraTransform();
    void SetADSAlpha(float DeltaSeconds);
    void SetWalkWeaponSway(float DeltaSeconds);
    void SetMoveInSides(float DeltaSeconds);
    void SetTurnWeaponSway(float DeltaSeconds);
    void GetLeftHandTransform();
    void GetRelativeRightHandTransform();
    void SetJumpShake(float DeltaSeconds);
    
    void InterpFinalRecoil(float DeltaSeconds);
    void InterpRecoil(float DeltaSeconds);

    void ResetJumpTimeline(); 

    #pragma region TimelineCode

    FTimeline TimeLineForModeInSides;
    FTimeline TimeLineForJump;
    

    FOnTimelineVector UpdateForModeInSides;
    FOnTimelineVector UpdateForJump;

    UFUNCTION()
    void TimeLineForWalkUpdate(FVector MoveVector);

    UFUNCTION()
    void TimeLineForJumpUpdate(FVector JumpVector);

    #pragma endregion TimelineCode

    FTimerHandle TimerForJumpTimelineReset;
    
    FTransform GetSocketTransform(USceneComponent* Object, FName Socket);
};

