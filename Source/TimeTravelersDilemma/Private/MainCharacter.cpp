// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "PaperSpriteComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
//#include "InputActionValue.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DataAssets.h"

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

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	AppendDataAssets();
	//implement EnhancedInput
	const APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
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

void AMainCharacter::AppendDataAssets()
{
	if (IsValid(SpeedDataAsset))
	{
		MovementSpeed = SpeedDataAsset->CharacterSpeed;
	}
}

void AMainCharacter::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
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
	}

}

