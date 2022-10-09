// Ace Game. All Rights Reserved.

#include "UI/AceBaseWidget.h"
#include "AceGameHUD.h"
#include "Player/AcePlayerCharacter.h"

void UAceBaseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    Character = Cast<AAcePlayerCharacter>(GetOwningPlayerPawn());
    CharacterController = Cast<APlayerController>(Character->GetController());
    HUD = Cast<AAceGameHUD>(CharacterController->GetHUD());
}

void UAceBaseWidget::ClearSlotAndDestroy(const bool DeleteInfoAboutAttachment)
{
}
