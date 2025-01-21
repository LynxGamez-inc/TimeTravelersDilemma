// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items.h"
#include "ItemLetter.generated.h"

class UPaperSpriteComponent;
/**
 * 
 */
UCLASS()
class TIMETRAVELERSDILEMMA_API AItemLetter : public AItems
{
	GENERATED_BODY()

public:
	AItemLetter();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPaperSpriteComponent> LetterSprite;

	void CanBeSeen(bool bIsVisible);
};
