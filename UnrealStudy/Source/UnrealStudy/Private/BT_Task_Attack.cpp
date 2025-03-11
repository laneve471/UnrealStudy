// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Task_Attack.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

#include "Kismet/KismetMathLibrary.h"

#include "MyAIController.h"
#include "MyEnemy.h"
#include "MyPlayer.h"

EBTNodeResult::Type UBT_Task_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto btNodeResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto curPawn = Cast<AMyEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (curPawn->IsValidLowLevel() == false)
		return btNodeResult;

	if (curPawn->IsAttack())
		return btNodeResult;

	auto player = Cast<AMyPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Player")));
	if (!player->IsValidLowLevel())
		return EBTNodeResult::Failed;

	auto quat = UKismetMathLibrary::FindLookAtRotation(curPawn->GetActorLocation(), player->GetActorLocation());

	curPawn->SetActorRotation(quat);
	curPawn->Attack_AI();

	return EBTNodeResult::Succeeded;
}
