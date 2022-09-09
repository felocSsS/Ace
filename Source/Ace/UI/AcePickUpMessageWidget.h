// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AcePickUpMessageWidget.generated.h"

class UTextBlock;

UCLASS()
class ACE_API UAcePickUpMessageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    void SetMessageText(const FText Text);
    
protected:
    UPROPERTY(meta=(BindWidget))
    UTextBlock* TextBlock;
    
private:
};
