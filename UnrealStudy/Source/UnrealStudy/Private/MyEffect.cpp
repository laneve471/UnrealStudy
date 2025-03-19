// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEffect.h"

#include "Components/SceneComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AMyEffect::AMyEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_sceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	_niagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("NiagaraComponent");
	_particleComponent = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystemComponent");

	RootComponent = _sceneComponent;
	_niagaraComponent->SetupAttachment(_sceneComponent);
	_particleComponent->SetupAttachment(_sceneComponent);
}

// Called when the game starts or when spawned
void AMyEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyEffect::SetParticle(UNiagaraSystem* particle)
{
	if (particle->IsValidLowLevel())
	{
		_niagaraComponent->SetAsset(particle);
		_niagaraComponent->OnSystemFinished.AddDynamic(this, &AMyEffect::Finished);
	}
}

void AMyEffect::SetParticle(UParticleSystem* particle)
{
	if (particle->IsValidLowLevel())
	{
		_particleComponent->SetTemplate(particle);
		_particleComponent->OnSystemFinished.AddDynamic(this, &AMyEffect::Finished_Particle);
	}
}

void AMyEffect::Play(FVector pos)
{
	SetActorLocation(pos);
	_niagaraComponent->Activate(true);
	_particleComponent->Activate(true);
}

void AMyEffect::Stop()
{
	_niagaraComponent->DeactivateImmediate();
	_particleComponent->DeactivateImmediate();
}

bool AMyEffect::IsActive()
{
	return _niagaraComponent->IsActive() || _particleComponent->IsActive();
}

void AMyEffect::Finished(UNiagaraComponent* PSystem)
{
	PSystem->DeactivateImmediate();
}

void AMyEffect::Finished_Particle(UParticleSystemComponent* PSystem)
{
	PSystem->DeactivateSystem();
}

