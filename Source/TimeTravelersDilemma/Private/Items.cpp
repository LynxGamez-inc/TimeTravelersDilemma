// Fill out your copyright notice in the Description page of Project Settings.


#include "Items.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"


// Sets default values
AItems::AItems()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AItems::OnBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AItems::OnEndOverlap);
	BoxCollision->SetGenerateOverlapEvents(true);
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	EquipWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("EquipWidget"));
	EquipWidget->SetupAttachment(BoxCollision);
	
}

// Called when the game starts or when spawned
void AItems::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItems::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItems::HideEquipWidget()
{
	EquipWidget->GetWidget()->SetVisibility(ESlateVisibility::Collapsed);
}

void AItems::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AItems::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
}

