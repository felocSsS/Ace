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
class UAceCharacterMovementComponent;

UCLASS()
class ACE_API UAcePlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
    void Fire();
    void StartJump();
    void FinishJump();
    void StartShooting();
    void EndShooting();
    void StartRunning();
    void StopRunning();
    
    float MoveRightValue;
    float MoveForwardValue;
    float ShakingModifier = 1.0f;

    bool bIsMovingRight = false;
    bool bIsMovingForward = false;
    
protected:
    virtual void NativeBeginPlay() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    UFUNCTION()
    void WeaponChanged(AAceBaseWeapon* NewWeapon);

    UFUNCTION()
    void UpdateInfo();

    UPROPERTY(BlueprintReadOnly, Category="Anim")
    float CharacterVelocity;
    
    UPROPERTY(BlueprintReadOnly, Category="Anim")
    float Direction;
    
    UPROPERTY(BlueprintReadOnly, Category="Anim")
    float CanAim;

    UPROPERTY(BlueprintReadOnly, Category="Anim")
    float CanEffect = 1.0f;

    UPROPERTY(BlueprintReadOnly, Category="Anim")
    float CanRunning = 1.0f;

    UPROPERTY(BlueprintReadOnly, Category="Anim")
    FRotator AimOffsetRotation;
    
    UPROPERTY(BlueprintReadOnly, Category="Anim")
    FRotator FinalTurnRotation;

    UPROPERTY(BlueprintReadOnly, Category="Recoil")
    FTransform RecoilTransform;
    
    UPROPERTY(BlueprintReadOnly, Category="Anim")
    FTransform RelativeCameraTransform;
    
    UPROPERTY(BlueprintReadOnly, Category="Anim")
    FTransform LeftHandTransform;
    
    UPROPERTY(BlueprintReadOnly, Category="Anim")
    FTransform RelativeHandTransform;
    
    UPROPERTY(BlueprintReadOnly, Category="Anim")
    FTransform SidesWeaponSway;

    UPROPERTY(BlueprintReadOnly, Category="Anim")
    FTransform JumpTransform;

    UPROPERTY(BlueprintReadOnly, Category="Anim")
    FTransform RunTransform;
    
    UPROPERTY(BlueprintReadOnly, Category="Anim")
    FVector WalkSwayLocation;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Anim")
    UCurveVector* WalkCurve;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Anim")
    UCurveVector* MoveInSidesCurve;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Anim")
    UCurveVector* JumpStartCurve;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Anim")
    UCurveVector* JumpEndCurve;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Anim")
    UCurveVector* RunVectorCurve;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Anim")
    UCurveVector* RunRotatorCurve;

    AAcePlayerCharacter* Character;
    
    APlayerController* PlayerController;

    UAceWeaponComponent* WeaponComponent;

    UAceCharacterMovementComponent* MovementComponent;
    
    AAceBaseWeapon* CurrentWeapon;

    float JumpPosition;
    float ZPositionJumpTransform;
    float IntermediateCanEffect = 1.0f;
    float IntermediateCanRunning = 1.0f;

    FTransform IntermediateRunTransform; // хз как "временная" на англ. 
    FTransform MoveInSidesSway;
    FTransform FinalRecoilTransform;
    
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
    void SetRunTransform(float DeltaSeconds);
    void InterpFinalRecoil(float DeltaSeconds);
    void InterpRecoil(float DeltaSeconds);
    void SetCanEffect(float DeltaSeconds);
    void SetCanRunning(float DeltaSeconds);
    void ResetJumpTimeline();


    #pragma region TimelineCode

    FTimeline TimeLineForModeInSides;
    FTimeline TimeLineForJump;
    FTimeline TimelineForRecoil;
    FTimeline TimelineForRun;
    
    FOnTimelineVector UpdateForModeInSides;
    FOnTimelineVector UpdateForJump;
    FOnTimelineVector UpdateForRecoil;
    FOnTimelineVector UpdateForRun1;
    FOnTimelineVector UpdateForRun2;

    FOnTimelineEvent TickForRun;

    UFUNCTION()
    void TimeLineForWalkUpdate(const FVector MoveVector);

    UFUNCTION()
    void TimeLineForJumpUpdate(const FVector JumpVector);

    UFUNCTION()
    void TimeLineForRecoilUpdate(const FVector RecoilVector);

    UFUNCTION()
    void TimeLineForRunUpdate();

    void RunUpdate(const FVector RunVector, const FVector RunRotator); 

    #pragma endregion TimelineCode

    FTimerHandle TimerForJumpTimelineReset;
    
    FTransform GetSocketTransform(USceneComponent* Object, FName Socket) const;
};