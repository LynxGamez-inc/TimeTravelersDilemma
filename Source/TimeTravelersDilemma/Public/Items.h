// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Items.generated.h"

class UWidgetComponent;
class UBoxComponent;

UCLASS()

class TIMETRAVELERSDILEMMA_API AItems : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AItems();
	
	UPROPERTY(EditDefaultsOnly, Category = "TimeTraveler|Components")
	TObjectPtr<UBoxComponent> BoxCollision;

protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "TimeTraveler|Components")
	TObjectPtr<UWidgetComponent> EquipWidget;

public:	
	
	virtual void Tick(float DeltaTime) override;

	void HideEquipWidget();
	
	UFUNCTION(BlueprintCallable)
	virtual void OnBeginOverlap( UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

private:
	

	
};

