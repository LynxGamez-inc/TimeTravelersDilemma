// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items.h"
#include "ItemBook.generated.h"

/**
 * 
 */

class UPaperSpriteComponent;
class UWidgetComponent;

UCLASS()
class TIMETRAVELERSDILEMMA_API AItemBook : public AItems
{
	GENERATED_BODY()

public:
	AItemBook();
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TimeTraveler|Components")
	TObjectPtr<UPaperSpriteComponent> BookSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TimeTraveler|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> WidgetComponent;
	
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;
};
