// Ace Game. All Rights Reserved.

#include "UI/AceGameHUD.h"
#include "AcePickUpMessageWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AcePlayerCharacter.h"
#include "Inventory/UI/AceInventoryWidget.h"

void AAceGameHUD::BeginPlay()
{
    Super::BeginPlay();

    if (!GetWorld()) return;
     
    Character = Cast<AAcePlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
    CharacterContoller = Cast<APlayerController>(Character->GetController());
    if (!Character) return;

    if (InventoryWidgetClass)
    {
        InventoryWidget = CreateWidget<UAceInventoryWidget>(GetWorld(), InventoryWidgetClass);
        InventoryWidget->SetOwningPlayer(CharacterContoller);   
    }
    
    if (PickUpMessageWidgetClass)
    {
        Character->OnInteractableItemChange.AddDynamic(this, &AAceGameHUD::OnInteractableItemChange);
        PickUpMessageWidget = CreateWidget<UAcePickUpMessageWidget>(GetWorld(), PickUpMessageWidgetClass);
        PickUpMessageWidget->SetOwningPlayer(CharacterContoller);
    }   
}

void AAceGameHUD::OnInteractableItemChange(bool ShowWidget, FText ItemName)
{
    if (!PickUpMessageWidget) return;
    ShowWidget ? PickUpMessageWidget->AddToViewport() : PickUpMessageWidget->RemoveFromViewport();
    ShowWidget ? PickUpMessageWidget->SetMessageText(ItemName) : PickUpMessageWidget->SetMessageText(FText());
}

void AAceGameHUD::ToggleInventory()
{
    if (InventoryWidget->IsInViewport())
    {
        InventoryWidget->RemoveFromViewport();
        CharacterContoller->SetInputMode(FInputModeGameOnly());
        CharacterContoller->bShowMouseCursor = false;
    }
    else
    {
        InventoryWidget->AddToViewport();
        CharacterContoller->SetInputMode(FInputModeGameAndUI());
        CharacterContoller->bShowMouseCursor = true;
    }
}