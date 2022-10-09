// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "AceInventoryDragDropOperation.generated.h"

class UAceBaseWidget;

UCLASS()
class ACE_API UAceInventoryDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Drag and Drop", meta=(ExposeOnSpawn="true"))
    UAceBaseWidget* WidgetFrom;
    
protected:

private:
};
