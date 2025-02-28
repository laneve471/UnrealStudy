// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHpBar.h"

#include "Kismet/KismetMathLibrary.h"
#include "Components/ProgressBar.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraActor.h"

void UMyHpBar::SetHpBarValue(float ratio)
{
	PB_HpBar->SetPercent(ratio);
}
