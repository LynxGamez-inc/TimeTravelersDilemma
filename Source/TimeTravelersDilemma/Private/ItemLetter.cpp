// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemLetter.h"
#include "TTCharacter/MainCharacter.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

AItemLetter::AItemLetter()
{
	RootComponent = BoxCollision;
	LetterSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("LetterSprite"));
	LetterSprite->SetupAttachment(RootComponent);

	VisibilityCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("VisibilityCollision"));
	VisibilityCollision->SetupAttachment(RootComponent);
	VisibilityCollision->OnComponentBeginOverlap.AddDynamic(this, &AItemLetter::OnVisibilityOverlap);
	VisibilityCollision->SetGenerateOverlapEvents(true);

	

	LetterSprite->SetVisibility(false);
}

void AItemLetter::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AItemLetter::OnBeginOverlap);
}

//sets letter to be visible
void AItemLetter::CanBeSeen(bool bIsVisible)
{
	if (LetterSprite)
	{
		LetterSprite->SetVisibility(bIsVisible);
	}
}

//Letter will be visible if lantern is Equipped
void AItemLetter::OnVisibilityOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMainCharacter* Character = Cast<AMainCharacter>(OtherActor))
	{
		if (Character->bIsLanternEquipped)
		{
			CanBeSeen(true);
		}
	}
}

void AItemLetter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                 AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp,
                                 int32 OtherBodyIndex,
                                 bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	
}

