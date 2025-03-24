// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */

// AMyActor : A... Actor
// UMyAnim : U... Actor가 아닌 것 => UObject

// 싱글캐스트 Delegate
// void(void)
DECLARE_DELEGATE(AnimDelegateTest)

// int(int, int)
DECLARE_DELEGATE_RetVal_TwoParams(int32, AnimDelegateTest2, int32, int32)

// 멀티캐스트 다이나믹 Delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnimDelegateTest3);

DECLARE_MULTICAST_DELEGATE(FAttackHitEvent);
DECLARE_MULTICAST_DELEGATE(FDeadEvent);

UCLASS()
class UNREALSTUDY_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMyAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds);

	UFUNCTION()
	void PlayAnimMontage();

	UFUNCTION()
	void AnimNotify_Attack_Hit();
	UFUNCTION()
	void AnimNotify_Dead();

	void JumpToSection(int32 sectionIndex);

	AnimDelegateTest _attackStart;
	AnimDelegateTest2 _attackStart2;

	UPROPERTY()
	FAnimDelegateTest3 _attackStart3;
	FAttackHitEvent _hitEvent;
	FDeadEvent _deadEvent;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	float _speed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	bool _isFalling = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"))
	bool _isDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* _animMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"))
	float _vertical;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage", meta = (AllowPrivateAccess = "true"))
	float _horizontal;
};
