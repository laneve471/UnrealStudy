// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

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
		_isFalling = character->GetCharacterMovement()->IsFalling();
	}
}
