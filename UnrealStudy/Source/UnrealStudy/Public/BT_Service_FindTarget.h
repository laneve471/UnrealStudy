// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BT_Service_FindTarget.generated.h"

/*
 BT_Service

  - 주기적으로 체크
  => 주기적으로 Player가 몬스터와 가까이 있는지 체크하고 BB에 기입
 */
UCLASS()
class UNREALSTUDY_API UBT_Service_FindTarget : public UBTService
{
	GENERATED_BODY()

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
