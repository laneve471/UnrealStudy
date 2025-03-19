// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyEffect.generated.h"

UCLASS()
class UNREALSTUDY_API AMyEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetParticle(class UNiagaraSystem* particle);
	void SetParticle(class UParticleSystem* particle);
	void Play(FVector pos);
	void Stop();

	bool IsActive();

	UFUNCTION()
	void Finished(class UNiagaraComponent* PSystem);
	UFUNCTION()
	void Finished_Particle(class UParticleSystemComponent* PSystem);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class USceneComponent* _sceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class UNiagaraComponent* _niagaraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class UParticleSystemComponent* _particleComponent;
};
