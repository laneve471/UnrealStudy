// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "MyDecalActor.generated.h"

DECLARE_MULTICAST_DELEGATE(FFieldAttack);
/**
 * 
 */
UCLASS()
class UNREALSTUDY_API AMyDecalActor : public ADecalActor
{
	GENERATED_BODY()
	
public:
	AMyDecalActor();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	FFieldAttack _attackEvent;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal", meta = (AllowPrivateAccess = "true"))
	float _areaRadius = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal", meta = (AllowPrivateAccess = "true"))
	float _delayTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal", meta = (AllowPrivateAccess = "true"))
	float _runTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal", meta = (AllowPrivateAccess = "true"))
	bool _bLoop = false;
};
