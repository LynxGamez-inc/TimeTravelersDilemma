// Fill out your copyright notice in the Description page of Project Settings.


#include "TTCharacter/MainCharacter.h"
#include "PaperFlipbookComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ItemLetter.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/InteractInterface.h"
#include "TTCharacter/DataAssets.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent=CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}


void AMainCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	AppendDataAssets();
	
}

void AMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//implement EnhancedInput
	PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		
		TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (IsValid(Subsystem))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (!IsValid(CharacterConfig))
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterConfig is not assigned in Blueprint for Character: %s. "
							  "Please assign it in the Blueprint."), *GetName());
		return;
	}

	//create pause widget
	if (IsValid(PauseWidgetClass))
	{
		PauseWidget = CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass);
	}
	if (IsValid(PauseWidget))
	{
		PauseWidget->AddToViewport();
		PauseWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}



void AMainCharacter::MoveForward(const FInputActionValue& Value)
{
	CurrentState=ECharacterState::ECS_Walk;
	FVector2d MoveActionValue=Value.Get<FVector2d>();
	
	if (abs(MoveActionValue.X)>0.0f)
	{
		const float DeltaTime = GetWorld()->GetDeltaSeconds();
		
		const FVector CurrentLocation=GetActorLocation();
		const FVector DistanceToMove=GetActorForwardVector()*MovementSpeed*MoveActionValue.X*DeltaTime;
		
		const FVector NewLocation= CurrentLocation+DistanceToMove;
		SetActorLocation(NewLocation);
		
		if (MoveActionValue.X < 0.0f)
		{
			GetSprite()->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
		}
		else if (MoveActionValue.X > 0.0f)
		{
			GetSprite()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
}

void AMainCharacter::PauseMenu()
{
 
	PauseWidget->SetVisibility(ESlateVisibility::Visible);
	DisableIMC();
	if (PlayerController)
	{
		// Set input mode to UI only
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(PauseWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);

		// Show mouse cursor
		PlayerController->bShowMouseCursor = true;
	}
}

void AMainCharacter::Jump()
{
	Super::Jump();
}

void AMainCharacter::Equip()
{
	if (IsValid(OverlappingActor))
	{
		// Check if the overlapping item implements the interactable interface
		if (OverlappingActor->Implements<UInteractInterface>())
		{
			// Call the Interact function on the item
			IInteractInterface::Execute_Interact(OverlappingActor, this);
		}
	}
}

void AMainCharacter::AppendDataAssets()
{
	if (IsValid(CharacterConfig))
	{
		MovementSpeed = CharacterConfig->CharacterSpeed;
	}
}

void AMainCharacter::AnimationUpdate()
{
	switch (CurrentState)
	{
	case ECharacterState::ECS_Idle:
		if (GetSprite()->GetFlipbook()!=FB_Idle)
		{
			GetSprite()->SetFlipbook(FB_Idle);
		}
		break;
		
	case ECharacterState::ECS_Walk:
		if (GetSprite()->GetFlipbook()!=FB_WalkForward)
		{
			GetSprite()->SetFlipbook(FB_WalkForward);
		}
		break;
		
	case ECharacterState::ECS_Jump:
		if (GetSprite()->GetFlipbook()!=FB_Jump)
		{
			GetSprite()->SetFlipbook(FB_Jump);
		}
		break;
	}
}



void AMainCharacter::SetOverlappingActor(AActor* Actor)
{
	OverlappingActor = Actor;
	OnOverlappingActorSet();
}

void AMainCharacter::OnOverlappingActorSet_Implementation()
{
	
}

void AMainCharacter::DisableIMC()
{
	if (IsValid(PlayerController))
	{
		TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem && InputMappingContext)
		{
			Subsystem->RemoveMappingContext(InputMappingContext);
		}
	}
}

void AMainCharacter::EnableIMC()
{
	if (IsValid(PlayerController))
	{
		TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem && InputMappingContext)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0); // Priority 0 as before
		}
	}
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (IsValid(EnhancedInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AMainCharacter::MoveForward);
		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Triggered,this,&AMainCharacter::Jump);
		EnhancedInputComponent->BindAction(EquipAction,ETriggerEvent::Triggered,this,&AMainCharacter::Equip);
		EnhancedInputComponent->BindAction(PauseAction,ETriggerEvent::Triggered,this,&AMainCharacter::PauseMenu);
	}

}

