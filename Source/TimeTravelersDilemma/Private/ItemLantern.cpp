 // Fill out your copyright notice in the Description page of Project Settings.


#include "ItemLantern.h"
#include "PaperSpriteComponent.h"
#include "TTCharacter/MainCharacter.h"
#include "Components/WidgetComponent.h"
#include "TTCharacter/DataAssets.h"


 AItemLantern::AItemLantern()
 {
  SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
  SpriteComponent->SetupAttachment(GetRootComponent());
 }

 void AItemLantern::BeginPlay()
 {
   Super::BeginPlay();
   EquipWidget->SetVisibility(false);
 }

 void AItemLantern::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                   AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp,
                                   int32 OtherBodyIndex,
                                   bool bFromSweep,
                                   const FHitResult& SweepResult)
 {
    Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
    MainCharacter = Cast<AMainCharacter>(OtherActor);
    if (IsValid(MainCharacter))
    {
     MainCharacter->SetOverlappingActor(this);
     EquipWidget->GetWidget()->SetVisibility(ESlateVisibility::Visible);
    }
 }


 void AItemLantern::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
 {
    Super::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

    MainCharacter = Cast<AMainCharacter>(OtherActor);
    
    if (IsValid(MainCharacter))
    {
      MainCharacter->SetOverlappingActor(nullptr);
      EquipWidget->GetWidget()->SetVisibility(ESlateVisibility::Collapsed);
    }
 }


void AItemLantern::Interact_Implementation(AActor* InstigatorActor)
 {
  // Ensure the instigator is a valid MainCharacter
  
  if (IsValid(MainCharacter))
  {
   if ( MainCharacter->GetSprite()->DoesSocketExist(MainCharacter->CharacterConfig->ItemSocket))
   {
    AttachToComponent(MainCharacter->GetSprite(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, MainCharacter->CharacterConfig->ItemSocket);
   }
  
  }
  }
 

