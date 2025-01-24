// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items.h"
#include "ItemLantern.generated.h"


class UPaperSpriteComponent;
/**
 * 
 */
UCLASS()
class TIMETRAVELERSDILEMMA_API AItemLantern : public AItems
{
	GENERATED_BODY()

	public:
	AItemLantern();
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPaperSpriteComponent> SpriteComponent;


	
	
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;
	
	
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;
	
};
