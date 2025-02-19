// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemLantern.h"
#include "ItemLetter.h"
#include  "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "MainCharacter.generated.h"


class UPaperSpriteComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UDataAssets;
class UUserWidget;



UCLASS()
class TIMETRAVELERSDILEMMA_API AMainCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	//user widget refernce
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY()
	UUserWidget* PauseWidget;

	
	// Enhanced Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput")
	TObjectPtr<UInputAction> EquipAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput")
	TObjectPtr<UInputAction> PauseAction;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MovementSpeed;

	//Boolians
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsLanternEquipped=false;
	


	//Setters & Getters
	FORCEINLINE void SetOverlappingItem(AItems* Item) {OverlappingItem = Item;}
	FORCEINLINE void SetLetterVisibility(AItemLetter* bIsVisible){}
	
	UFUNCTION(BlueprintCallable, Category = "Enhanced Input")
	void DisableIMC();
	
	UFUNCTION(BlueprintCallable, Category = "Enhanced Input")
	void EnableIMC();

	//FlipBooks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flipbooks")
	UPaperFlipbook* FB_Idle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flipbooks")
	UPaperFlipbook* FB_WalkForward;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Assets")
	TObjectPtr<UDataAssets> CharacterConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController;
	
	UFUNCTION(BlueprintCallable, Category = "Enhanced Input")
	void MoveForward(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Enhanced Input")
	void PauseMenu();
	
	virtual void Jump() override;
	void Equip();
	
	void AppendDataAssets();

	

	
	

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<AItems> OverlappingItem;

	UPROPERTY(EditAnywhere)
	TObjectPtr<AItemLetter> ItemLetterInstance;
};
