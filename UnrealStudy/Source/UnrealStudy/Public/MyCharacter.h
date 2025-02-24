// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class UNREALSTUDY_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const struct FInputActionValue& value);
	void Look(const struct FInputActionValue& value);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* _moveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* _lookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* _jumpAction;

	// 언리얼의 핵심 구조
	// 1. 상속
	// 2. 컴포넌트 패턴
	// 
	// 컴포넌트 : 객체나 씬의 기능을 나누고 조립할 수 있도록 하는 개별적인 부품
	// 1. Actor 컴포넌트
	//		- 동작 담당
	//		- 이동, 점프, 체력 등
	//		- 공간적 요소는 없음
	// 2. Scene 컴포넌트
	//		- 공간적인 개념
	//		- 어디에 배치되는지 결정
	//		- 눈에 보이는 무언가 (카메라, 광원, 모델)
	//		- 다른 컴포넌트에 붙을 수 있음 (부모가 움직이면 자식도 움직임)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* _camera; // 액터에만 붙을 수 있음

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* _springArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	float _speed = 10.0f;
};
