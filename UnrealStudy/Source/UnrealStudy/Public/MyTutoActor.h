// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTutoActor.generated.h"

// 1. 메모리
// 2. 리플렉션(Reflection)
UCLASS() // UObject를 상속받는 클래스
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

// actor가 월드에 존재하려면
// 1. transform(4x4 행렬) -> 존재 자체
// 2. mesh 필요 -> 눈에 보임
// 3. material 필요 -> 색을 칠함

private:
	UPROPERTY()
	UStaticMeshComponent* _mesh;

	float _angle = 0.f;
	float _orbitSpeed = 3.0f;
	float _orbitRadius = 300.0f;
};
