// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items.h"
#include "ItemLetter.generated.h"

class UPaperSpriteComponent;
class UBoxComponent;
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

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UBoxComponent> VisibilityCollision;

	void CanBeSeen(bool bIsVisible);

	UFUNCTION()
	void OnVisibilityOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
							 const FHitResult& SweepResult);
	
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;
	
	
};
