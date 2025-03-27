// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TIMETRAVELERSDILEMMA_API IInteractInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Interact function with an Actor input
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "TimerTraverler|Interaction")
	void Interact(AActor* InstigatorActor);

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "TimerTraverler|Interaction")
	void ConversationClosed();

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "TimerTraverler|Interaction")
	void SetInteractableState(bool bCanShowInteract);
};
