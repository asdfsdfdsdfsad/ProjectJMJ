// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_PatrolLogic.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJMJ_API UBTTask_PatrolLogic : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	float Radius = 500.0f;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
