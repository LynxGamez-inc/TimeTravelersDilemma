// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemLetter.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

AItemLetter::AItemLetter()
{
	LetterSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("LetterSprite"));
	LetterSprite->SetupAttachment(BoxCollision);
	RootComponent = BoxCollision;
 
}

void AItemLetter::CanBeSeen(bool bIsVisible)
{
	if (LetterSprite)
	{
		LetterSprite->SetVisibility(bIsVisible);
	}
}


