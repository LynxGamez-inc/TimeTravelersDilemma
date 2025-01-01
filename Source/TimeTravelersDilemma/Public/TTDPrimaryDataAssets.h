// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TTDPrimaryDataAssets.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TIMETRAVELERSDILEMMA_API UTTDPrimaryDataAssets : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CharacterSpeed;
};
