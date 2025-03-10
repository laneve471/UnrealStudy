// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "MyButton.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSTUDY_API UMyButton : public UButton
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void SetCurIndex();

	// 인벤토리 없이는 쓸 수 없음 -> 높은 결합도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMyInvenUI* widget;

	int32 _buttonIndex = -1;
};
