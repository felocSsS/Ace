// Ace Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/AceBaseItem.h"
#include "AceBaseItemObject.generated.h"

UCLASS(Blueprintable)
class ACE_API UAceBaseItemObject : public UObject
{
	GENERATED_BODY()

public:
    //test

    UFUNCTION(BlueprintCallable)
    void BPGetIcon(UTexture2D*& BPIcon);
    
    UFUNCTION(BlueprintCallable)
    void BPGetName(FText& BPName);
    
    UFUNCTION(BlueprintCallable)
    void BPGetClass(TSubclassOf<AAceBaseItem>& Class);
    
    //test
    
    UTexture2D* GetObjectIcon() const;
    FText GetObjectName() const;
    TSubclassOf<AAceBaseItem> GetObjectClass() const;
    void SetClass(TSubclassOf<AAceBaseItem> Class);
    void SetIcon(UTexture2D* Image);
    void SetName(FText Text);
    
protected:
    UTexture2D* Icon;
    
    FText Name;
    
    TSubclassOf<AAceBaseItem> ItemClass;
    
private:
    
};
