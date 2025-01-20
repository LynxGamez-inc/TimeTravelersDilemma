 // Fill out your copyright notice in the Description page of Project Settings.


#include "ItemLantern.h"
#include "PaperSpriteComponent.h"
#include "MainCharacter.h"
#include "Components/WidgetComponent.h"


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
    GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, "Overlapping Item Lantern");
    TObjectPtr<AMainCharacter> MainCharacter = Cast<AMainCharacter>(OtherActor);
    if (IsValid(MainCharacter))
    {
     MainCharacter->SetOverlappingItem(this);
     EquipWidget->GetWidget()->SetVisibility(ESlateVisibility::Visible);
    }
 }


 void AItemLantern::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
 {
    Super::OnEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

    TObjectPtr<AMainCharacter> MainCharacter = Cast<AMainCharacter>(OtherActor);
    
    if (IsValid(MainCharacter))
    {
      MainCharacter->SetOverlappingItem(nullptr);
      EquipWidget->GetWidget()->SetVisibility(ESlateVisibility::Collapsed);
    }
 }


