// Ace Game. All Rights Reserved.

#include "UI/AceGameHUD.h"
#include "AcePickUpMessageWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AcePlayerCharacter.h"

void AAceGameHUD::BeginPlay()
{
    Super::BeginPlay();

    if (!GetWorld()) return;
     
    const auto Player = Cast<AAcePlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
    Player->OnInteractableItemChange.AddDynamic(this, &AAceGameHUD::OnInteractableItemChange);

    PickUpMessageWidget = CreateWidget<UAcePickUpMessageWidget>(GetWorld(), PickUpMessageWidgetClass);
}

void AAceGameHUD::OnInteractableItemChange(bool ShowWidget, FText ItemName)
{
    if (!PickUpMessageWidget) return;
    ShowWidget ? PickUpMessageWidget->AddToViewport() : PickUpMessageWidget->RemoveFromViewport();
    ShowWidget ? PickUpMessageWidget->SetMessageText(ItemName) : PickUpMessageWidget->SetMessageText(FText());
}
