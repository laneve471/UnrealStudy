// Fill out your copyright notice in the Description page of Project Settings.

#include "MyItem.h"

#include "Components/CapsuleComponent.h"
#include "MyCharacter.h"
#include "MyPlayer.h"
#include "MyPlayerController.h"

// Sets default values
AMyItem::AMyItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));

	_mesh->SetupAttachment(_collider);

	RootComponent = _collider;
}

void AMyItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_collider->OnComponentBeginOverlap.AddDynamic(this , &AMyItem::OnOverlap);
}

// Called when the game starts or when spawned
void AMyItem::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyItem::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult)
{
	auto character = Cast<AMyPlayer>(OtherActor);
	auto player = Cast<AMyPlayerController>(character->GetController());

	if (character && player)
	{
		UE_LOG(LogTemp, Log, TEXT("%s"), *character->GetName());

		character->AddHp(10);
		character->AddItem(this);

		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}
}

