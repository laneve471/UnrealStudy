// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTutoActor.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMyTutoActor::AMyTutoActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = _mesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		sm(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'"));

	if (sm.Succeeded())
	{
		_mesh->SetStaticMesh(sm.Object);
	}
}

// Called when the game starts or when spawned
void AMyTutoActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyTutoActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetAttachParentActor() != nullptr)
	{
		FVector parentV = GetAttachParentActor()->GetActorLocation();
		FVector myV = GetActorLocation();

		FRotator rot = UKismetMathLibrary::FindLookAtRotation(myV, parentV);
		SetActorRotation(rot);

		_angle += _orbitSpeed * DeltaTime;
		FVector newV = parentV + FVector(FMath::Cos(_angle) * _orbitRadius,
											FMath::Sin(_angle) * _orbitRadius, 0);
		SetActorLocation(newV);
	}
}

