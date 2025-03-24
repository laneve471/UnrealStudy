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

	UFUNCTION()
	void TestDelegate();
	UFUNCTION()
	int32 TestDelegate2(int32 a, int32 b);

	UFUNCTION()
	void AttackEnd(class UAnimMontage* Montage, bool bInterrupted);

	virtual void Attack_Hit();
	UFUNCTION()
	void DeadEvent();

	void AddHp(float Amount);
	void SubtractHp(float Amount);

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	// 실제 나에게 적용된 데미지 반환

	bool IsDead();
	bool IsAttack() { return _isAttack; }

	float My_Vertical() { return _vertical; }
	float My_Horizontal() { return _horizontal; }
	float GetAttackRange() { return _attackRange; }

protected:
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

	UPROPERTY()
	class UMyAnimInstance* _animInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat", meta = (AllowPrivateAccess = "true"))
	class UMyStatComponent* _statComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	bool _isAttack;

	int32 _curAttackSection = 0;

	float _vertical = 0.0f;
	float _horizontal = 0.0f;

	UPROPERTY(EditAnywhere)
	float _attackRange = 300.f;
};

// 액터 : mesh, material, transform
// 폰 : input controller, movement 추가
// 캐릭터 : skeletal mesh, capsule, anim 추가

// 클래스는 객체가 아님