// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSTUDY_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMyAIController();

	// Controller가 Pawn에 빙의될 때 호출되는 함수
	virtual void OnPossess(APawn* InPawn) override;
	// Controller 빙의가 해제될 때 호출되는 함수
	virtual void OnUnPossess() override;

	UFUNCTION()
	void RandMove();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBlackboardData* _blackBoard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBehaviorTree* _behaviorTree;

private:
	UPROPERTY()
	FTimerHandle _timerHandle;
};
