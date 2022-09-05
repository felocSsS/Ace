// Ace Game. All Rights Reserved.

#include "Objects/AceBaseItemObject.h"

UTexture2D* UAceBaseItemObject::GetObjectIcon() const
{
    if (!Icon) return nullptr;

    return Icon;
}

FText UAceBaseItemObject::GetObjectName() const
{
    return Name;
}

TSubclassOf<AAceBaseItem> UAceBaseItemObject::GetObjectClass() const
{
    return ItemClass;
}

void UAceBaseItemObject::SetClass(TSubclassOf<AAceBaseItem> Class)
{
    ItemClass = Class;
}

void UAceBaseItemObject::SetIcon(UTexture2D* Image)
{
    Icon = Image;
}

void UAceBaseItemObject::SetName(FText Text)
{
    Name = Text;
}

void UAceBaseItemObject::BPGetIcon(UTexture2D*& BPIcon)
{
    BPIcon = GetObjectIcon();
}

void UAceBaseItemObject::BPGetName(FText& BPName)
{
    BPName = GetObjectName();
}

void UAceBaseItemObject::BPGetClass(TSubclassOf<AAceBaseItem>& Class)
{
    Class = GetObjectClass();
}