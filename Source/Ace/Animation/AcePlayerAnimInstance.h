// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AcePlayerAnimInstance.generated.h"

class AAcePlayerCharacter;
class AAceBaseWeapon;
class UAceWeaponComponent;

UCLASS()
class ACE_API UAcePlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, Category="Recoil")
    FTransform RecoilTransform;
    UPROPERTY(BlueprintReadOnly, Category="Recoil")
    FTransform FinalRecoilTransform;
    
protected:
    virtual void NativeBeginPlay() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    UFUNCTION()
    virtual void WeaponChanged(AAceBaseWeapon* NewWeapon);

    UPROPERTY(BlueprintReadOnly, Category="Character")
    AAcePlayerCharacter* Character;

    AAceBaseWeapon* CurrentWeapon;
    
    UAceWeaponComponent* WeaponComponent;

    APlayerController* PlayerController;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anim")
    float Velocity;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anim")
    float Direction;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anim")
    float ADSAlpha;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anim")
    FRotator ActualRotation;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anim")
    FRotator AimOffsetRotation;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="test")
    FTransform CameraTransform;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="test")
    FTransform RelativeCameraTransform;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="test")
    FTransform RHandToSightsTransform;
    
private:
    void SetADSAlpha(float DeltaSeconds);
    void SetAimOffset();
    void SetCharacterVars();
    void SetRelativeCameraTransform();
    virtual void SetIKTransforms();
    
    FTransform GetSocketTransform(USceneComponent* Object, FName Socket);
};
