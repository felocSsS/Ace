// Ace Game. All Rights Reserved.

#include "UI/AcePickUpMessageWidget.h"
#include "Components/TextBlock.h"

void UAcePickUpMessageWidget::SetMessageText(const FText Text)
{
    FString MessageText = FString("Press F to PickUp ").Append(Text.ToString());
    TextBlock->SetText(FText::FromString(MessageText));
}
