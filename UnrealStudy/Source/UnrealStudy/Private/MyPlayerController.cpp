// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "EnhancedInputSubSystems.h"
#include "Engine/LocalPlayer.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay(); // Super : ºÎ¸ð

	UEnhancedInputLocalPlayerSubsystem* subSystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (subSystem)
	{
		subSystem->AddMappingContext(_inputMappingContext, 0);
	}
}
