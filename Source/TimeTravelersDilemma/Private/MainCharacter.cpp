// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "PaperSpriteComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DataAssets.h"
#include "MovieSceneTracksComponentTypes.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(GetRootComponent());

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
	const TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		
		TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
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
}



void AMainCharacter::MoveForward(const FInputActionValue& Value)
{
	FVector2d MoveActionValue=Value.Get<FVector2d>();
	
	if (abs(MoveActionValue.X)>0.0f)
	{
		float DeltaTime = GetWorld()->GetDeltaSeconds();
		
		FVector CurrentLocation=GetActorLocation();
		FVector DistanceToMove=GetActorForwardVector()*MovementSpeed*MoveActionValue.X*DeltaTime;
		
		FVector NewLocation= CurrentLocation+DistanceToMove;
		SetActorLocation(NewLocation);
	}
	
}

void AMainCharacter::Jump()
{
	Super::Jump();
}

void AMainCharacter::Equip()
{
	if (IsValid(OverlappingItem))
	{
		if (SpriteComponent->DoesSocketExist(CharacterConfig->ItemSocket))
		{
			OverlappingItem->AttachToComponent(SpriteComponent,FAttachmentTransformRules::SnapToTargetNotIncludingScale,CharacterConfig->ItemSocket);
			OverlappingItem->HideEquipWidget();
			bIsLanternEquipped=true;
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



// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AMainCharacter::MoveForward);
		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Triggered,this,&AMainCharacter::Jump);
		EnhancedInputComponent->BindAction(EquipAction,ETriggerEvent::Triggered,this,&AMainCharacter::Equip);
	}

}

