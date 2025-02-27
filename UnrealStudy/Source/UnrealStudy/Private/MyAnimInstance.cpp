// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

#include "MyCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Animation/AnimMontage.h"

UMyAnimInstance::UMyAnimInstance()
{
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	auto pawn = TryGetPawnOwner();

	AMyCharacter* character = Cast<AMyCharacter>(pawn); // dynamicCast
	if (character != nullptr)
	{
		_speed = character->GetVelocity().Size();
		// UE_LOG(LogTemp, Error, TEXT("Speed : %f"), _speed);
		_isFalling = character->GetMovementComponent()->IsFalling();
		_vertical = character->My_Vertical();
		_horizontal = character->My_Horizontal();
	}
}

void UMyAnimInstance::PlayAnimMontage()
{
	if (_animMontage == nullptr)
		return;

	if (!Montage_IsPlaying(_animMontage))
	{
		// Attack Delegate 실행
		//_attackStart.Execute();
		//_attackStart2.Execute(_speed, _isFalling);
		//_attackStart3.Broadcast(); // 멀티캐스트
		Montage_Play(_animMontage);
	}
}

void UMyAnimInstance::AnimNotify_Attack_Hit()
{
	_hitEvent.Broadcast();
}

void UMyAnimInstance::JumpToSection(int32 sectionIndex)
{
	// Section1, Section2, Section3
	FName sectionName = FName(*FString::Printf(TEXT("Section%d"), sectionIndex));
	Montage_JumpToSection(sectionName);
}
