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
    if (!Character || !CharacterContoller) return;

    if (InventoryWidgetClass)
    {
        InventoryWidget = CreateWidget</*UAceInventoryWidget*/UUserWidget>(GetWorld(), InventoryWidgetClass);
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
    //ShowWidget ? PickUpMessageWidget->AddToViewport() : PickUpMessageWidget->RemoveFromViewport();
    //ShowWidget ? PickUpMessageWidget->SetMessageText(ItemName) : PickUpMessageWidget->SetMessageText(FText());
    if (ShowWidget)
    {
        PickUpMessageWidget->SetMessageText(ItemName);
        if (!PickUpMessageWidget->IsInViewport())
            PickUpMessageWidget->AddToViewport();
    }
    else
    {
        PickUpMessageWidget->SetMessageText(FText());
        if (PickUpMessageWidget->IsInViewport())
            PickUpMessageWidget->RemoveFromViewport();
    }
}

void AAceGameHUD::ToggleInventory()
{
    if (InventoryWidget->IsInViewport() && CharacterContoller)
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