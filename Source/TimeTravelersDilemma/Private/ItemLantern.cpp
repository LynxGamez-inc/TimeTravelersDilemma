 // Fill out your copyright notice in the Description page of Project Settings.


#include "ItemLantern.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "MainCharacter.h"


 AItemLantern::AItemLantern()
 {
  
  BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
  RootComponent = BoxCollision;
  BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AItemLantern::OnBeginOverlap);
  BoxCollision->SetGenerateOverlapEvents(true);
  
  SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
  SpriteComponent->SetupAttachment(GetRootComponent());
 
 }

 void AItemLantern::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
 {
  Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
  GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, "Overlapping Item Lantern");
  TObjectPtr<AMainCharacter> MainCharacter = Cast<AMainCharacter>(OtherActor);
  
  if (MainCharacter)
  {
   // Attach to the character's hand
   MainCharacter->AttachLantern(this);
  }
 }
