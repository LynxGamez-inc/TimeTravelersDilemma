// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "TTCharacter/MainCharacter.h"
#include "CoreMinimal.h"
#include  "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "MainCharacter.generated.h"


class AItems;
class UPaperSpriteComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UDataAssets;
class UUserWidget;
class AItemLetter;


//Enums
UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Idle UMETA(DisplayName = "Idle"),
	ECS_Walk UMETA(DisplayName = "Walk"),
	ECS_Jump UMETA(DisplayName = "Jump")
};

UCLASS()
class TIMETRAVELERSDILEMMA_API AMainCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	
	AMainCharacter();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TimerTraverler|Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "TimerTraverler|Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	//user widget reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimerTraverler|UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> PauseWidget;

	
	// Enhanced Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimerTraverler|EnhancedInput")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimerTraverler|EnhancedInput")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimerTraverler|EnhancedInput")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimerTraverler|EnhancedInput")
	TObjectPtr<UInputAction> EquipAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimerTraverler|EnhancedInput")
	TObjectPtr<UInputAction> PauseAction;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MovementSpeed;

	//Boolean
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsLanternEquipped=false;


	//Setters & Getters
	UFUNCTION(BlueprintCallable,Category = "TimerTraverler|Interaction")
	void SetOverlappingActor(AActor* Actor);
	
	FORCEINLINE void SetLetterVisibility(AItemLetter* bIsVisible){}
	
	UFUNCTION(BlueprintCallable, Category = "TimerTraverler|Enhanced Input")
	void DisableIMC();
	
	UFUNCTION(BlueprintCallable, Category = "TimerTraverler|Enhanced Input")
	void EnableIMC();
	
	//states
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimerTraverler|Animation")
	ECharacterState CurrentState;

	//FlipBooks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimerTraverler|Flipbooks")
	TObjectPtr<UPaperFlipbook> FB_Idle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimerTraverler|Flipbooks")
	TObjectPtr<UPaperFlipbook> FB_WalkForward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimerTraverler|Flipbooks")
	TObjectPtr<UPaperFlipbook> FB_Jump;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimerTraverler|Data Assets")
	TObjectPtr<UDataAssets> CharacterConfig;
	
protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController;
	
	UFUNCTION(BlueprintCallable, Category = "TimerTraverler|Enhanced Input")
	void MoveForward(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "TimerTraverler|Enhanced Input")
	void PauseMenu();
	
	virtual void Jump() override;
	void Equip();
	
	void AppendDataAssets();

	void AnimationUpdate();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "TimerTraverler|Interaction")
	void OnOverlappingActorSet();
	

private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess=true))
	TObjectPtr<AActor> OverlappingActor;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AItemLetter> ItemLetterInstance;
};
