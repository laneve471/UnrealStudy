// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTutoActor.generated.h"

// 1. �޸�
// 2. ���÷���(Reflection)
UCLASS() // UObject�� ��ӹ޴� Ŭ����
class UNREALSTUDY_API AMyTutoActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTutoActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// actor�� ���忡 �����Ϸ���
// 1. transform(4x4 ���) -> ���� ��ü
// 2. mesh �ʿ� -> ���� ����
// 3. material �ʿ� -> ���� ĥ��

private:
	UPROPERTY()
	UStaticMeshComponent* _mesh;

	float _angle = 0.f;
	float _orbitSpeed = 3.0f;
	float _orbitRadius = 300.0f;
};
