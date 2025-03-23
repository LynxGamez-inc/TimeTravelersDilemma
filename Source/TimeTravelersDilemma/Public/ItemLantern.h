// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items.h"
#include "Interfaces/InteractInterface.h"
#include "ItemLantern.generated.h"


class UPaperSpriteComponent;
class AMainCharacter;
/**
 * 
 */
UCLASS()
class TIMETRAVELERSDILEMMA_API AItemLantern : public AItems,public  IInteractInterface
{
	GENERATED_BODY()

	public:
	AItemLantern();
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TimeTraveler|Components")
	TObjectPtr<UPaperSpriteComponent> SpriteComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TimeTraveler|Character")
	TObjectPtr<AMainCharacter> MainCharacter;
	
	
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

	virtual void Interact_Implementation(AActor* InstigatorActor) override;
	
};
