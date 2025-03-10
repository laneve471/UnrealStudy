// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AMyAIController::AMyAIController()
{
}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// 3초마다 반복적으로 RandMove 함수 호출
	//GetWorld()->GetTimerManager().SetTimer(_timerHandle, this, &AMyAIController::RandMove, 3.0f, true);
	
	UBlackboardComponent* temp = Blackboard;
	if (UseBlackboard(_blackBoard, temp))
	{
		if (RunBehaviorTree(_behaviorTree))
		{

		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("BT failed."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BB failed."));
	}
}

void AMyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	//GetWorld()->GetTimerManager().ClearTimer(_timerHandle);
}

void AMyAIController::RandMove()
{
	auto curPawn = GetPawn(); // 현재 빙의되어 있는 폰

	if (curPawn->IsValidLowLevel() == false)
		return;

	// 현재 설정한 NavMesh를 갖고 오는 것
	auto navMesh = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (navMesh->IsValidLowLevel() == false)
		return;

	// 랜덤한 위치...=> NavMesh 물어보기
	FNavLocation randLocation;

	if (navMesh->GetRandomPointInNavigableRadius(curPawn->GetActorLocation(), 100.0f, randLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, randLocation.Location);
	}
}
