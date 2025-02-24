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

UCLASS()
class UNREALSTUDY_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMyAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	float _speed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	bool _isFalling = false;
};
