// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEffectManager.h"

#include "NiagaraSystem.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AMyEffectManager::AMyEffectManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	CreateEffect(TEXT("SparrowHit"), TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSparrow/FX/Particles/Sparrow/Abilities/Primary/FX/P_Sparrow_HitHero.P_Sparrow_HitHero'"));
	CreateEffect(TEXT("FireArrowHit"), TEXT("/Script/Niagara.NiagaraSystem'/Game/Graphics/Effect/MixedVFX/Particles/Projectiles/Hits/NS_FireArrow_Hit.NS_FireArrow_Hit'"));
	UE_LOG(LogTemp, Log, TEXT(""));
}

// Called when the game starts or when spawned
void AMyEffectManager::BeginPlay()
{
	Super::BeginPlay();
	
	for (auto particle : _particleTable)
	{
		FString name = particle.Key;
		_effectTable.Add(name);

		for (int i = 0; i < 5; i++)
		{
			auto effect = GetWorld()->SpawnActor<AMyEffect>(FVector::ZeroVector, FRotator::ZeroRotator);
			effect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			auto niagara = Cast<UNiagaraSystem>(_particleTable[name]);
			if (niagara)
			{
				effect->SetParticle(niagara);
			}
			else
			{
				effect->SetParticle(Cast<UParticleSystem>(_particleTable[name]));
			}

			effect->Stop();

			_effectTable[name]._effects.Add(effect);
		}
	}
}

// Called every frame
void AMyEffectManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyEffectManager::CreateEffect(FString key, FString path)
{
	ConstructorHelpers::FObjectFinder<UFXSystemAsset> particle(*path);
	if (particle.Succeeded())
	{
		_particleTable.Add(key, particle.Object);
	}
}

void AMyEffectManager::PlayEffect(FString key, FVector pos)
{
	auto effects = _effectTable.Find(key);
	if (!effects)
		return;

	auto iter = effects->_effects.FindByPredicate([](AMyEffect* effect)->bool
		{
			return !effect->IsActive();
		});

	if (iter)
	{
		(*iter)->Play(pos);
	}
}

