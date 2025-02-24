// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBook.h"
#include "PaperSpriteComponent.h"
#include "Components/WidgetComponent.h"


AItemBook::AItemBook()
{
	BookSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BookSprite"));
	BookSprite->SetupAttachment(GetRootComponent());

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetRootComponent());
}

void AItemBook::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemBook::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Collision Successful!"));
	
}



