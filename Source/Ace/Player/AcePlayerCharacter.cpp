// Ace Game. All Rights Reserved.

#include "Player/AcePlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Animation/AcePlayerAnimInstance.h"
#include "Blueprint/UserWidget.h"
#include "Components/AceInventoryComponent.h"
#include "Components/AceWeaponComponent.h"
#include "GameFramework/GameModeBase.h"
#include "Items/AceBaseInteractableItem.h"

AAcePlayerCharacter::AAcePlayerCharacter()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(GetMesh(), "head");
    CameraComponent->bUsePawnControlRotation = true;

    GetMesh()->bVisibleInReflectionCaptures= true;
    GetMesh()->bCastHiddenShadow = true;
    
    ClientMesh = CreateDefaultSubobject<USkeletalMeshComponent>("ClientMesh");
    ClientMesh->SetCastShadow(false);
    ClientMesh->bCastHiddenShadow = false;
    ClientMesh->bVisibleInReflectionCaptures = false;
    ClientMesh->SetTickGroup(ETickingGroup::TG_PostPhysics);
    ClientMesh->SetupAttachment(GetMesh());

    InventoryComponent = CreateDefaultSubobject<UAceInventoryComponent>("InventoryComponent");
}

void AAcePlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    AnimInstance = Cast<UAcePlayerAnimInstance>(GetMesh()->GetAnimInstance());
    ADSAlpha = 0.0f;
    ClientMesh->HideBoneByName("neck_01", PBO_None);
    GetMesh()->SetVisibility(false);
}

void AAcePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAcePlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAcePlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AAcePlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &AAcePlayerCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UAceWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UAceWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AAcePlayerCharacter::Aim);
    PlayerInputComponent->BindAction("Aim", IE_Released, this, &AAcePlayerCharacter::ResetAim);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UAceWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UAceWeaponComponent::Reload);
    PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AAcePlayerCharacter::PickUpItem);
    PlayerInputComponent->BindAction("ToggleInventory", IE_Pressed, this, &AAcePlayerCharacter::OpenInventory);
}

void AAcePlayerCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    TryFindInteractableItem();
}

void AAcePlayerCharacter::TryFindInteractableItem()
{
    if (!GetWorld()) return;

    FHitResult HitResult;
    FVector TraceStart, TraceEnd;
    GetTraceData(TraceStart, TraceEnd);
    
    FCollisionObjectQueryParams CollisionObjectTypes;
    CollisionObjectTypes.AddObjectTypesToQuery(ECollisionChannel::ECC_EngineTraceChannel3);
    
    GetWorld()->LineTraceSingleByObjectType(HitResult, TraceStart, TraceEnd, CollisionObjectTypes);
    
    if (HitResult.bBlockingHit)
    {
        if (Item != HitResult.GetActor())
        {
            Item = Cast<AAceBaseInteractableItem>(HitResult.GetActor());
            ItemDirty = true;
            OnInteractableItemChange.Broadcast(true, Item->GetItemName());
        }
    }
    else
    {
        if (ItemDirty)
        {
            Item = nullptr;
            ItemDirty = false;
            OnInteractableItemChange.Broadcast(false, FText());
        }
    }
}

void AAcePlayerCharacter::GetTraceData(FVector& TraceStart, FVector& TraceEnd)
{
    const auto AceController = GetController<APlayerController>();
    if (!AceController) return;
    
    FVector ViewLocation;
    FRotator ViewRotation;
    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    
    TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + ShootDirection * 150;
}

void AAcePlayerCharacter::PickUpItem()
{
    InventoryComponent->AddItem(Item->GetItemObject());
    Item->Destroy();
    Item = nullptr;
    OnInteractableItemChange.Broadcast(false, FText());
}

void AAcePlayerCharacter::OpenInventory()
{
    
}

void AAcePlayerCharacter::MoveForward(float Value)
{
    if(!AnimInstance) return;
    
	if (Value == 0.0f)
	{
	    AnimInstance->bIsMovingForward = false;
	}
    else
    {
        AddMovementInput(GetActorForwardVector(), Value);
        AnimInstance->MoveForwardValue = Value;
        AnimInstance->bIsMovingForward = true;
    }
}

void AAcePlayerCharacter::MoveRight(float Value)
{
    if(!AnimInstance) return;

	if (Value == 0.0f)
	{
	    AnimInstance->bIsMovingRight = false;    
	}
    else
    {
        AddMovementInput(GetActorRightVector(), Value);
        AnimInstance->MoveRightValue = Value;
        AnimInstance->bIsMovingRight = true;
    }
}

void AAcePlayerCharacter::Aim()
{
    ADSAlpha = 1.0f;
    GetMesh()->SetTickGroup(TG_PostUpdateWork);
    if (AnimInstance)
        AnimInstance->ShakingModifier = 0.1;
   //CameraComponent->SetFieldOfView(60);
}

void AAcePlayerCharacter::ResetAim()
{
    ADSAlpha = 0.0f;
    GetMesh()->SetTickGroup(TG_PrePhysics);
    if (AnimInstance)
        AnimInstance->ShakingModifier = 1.0f;
    //CameraComponent->SetFieldOfView(90);
}