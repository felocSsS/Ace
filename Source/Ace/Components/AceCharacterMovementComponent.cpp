// Ace Game. All Rights Reserved.

#include "Components/AceCharacterMovementComponent.h"
#include "Player/AcePlayerCharacter.h"

float UAceCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const auto Character = Cast<AAcePlayerCharacter>(GetPawnOwner());

    return Character && Character->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed; 
}
