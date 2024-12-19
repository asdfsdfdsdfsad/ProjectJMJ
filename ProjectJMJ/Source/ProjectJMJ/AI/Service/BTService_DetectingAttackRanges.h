// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_DetectingAttackRanges.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJMJ_API UBTService_DetectingAttackRanges : public UBTService
{
	GENERATED_BODY()
public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
	UPROPERTY(EditAnywhere, Category = "Set AI")
	FBlackboardKeySelector Target;
	UPROPERTY(EditAnywhere, Category = "Set AI")
	FBlackboardKeySelector AttackRange;
	UPROPERTY(EditAnywhere, Category = "Out AI")
	FBlackboardKeySelector IsAttack;
	UPROPERTY(EditAnywhere, Category = "Out AI")
	FBlackboardKeySelector TargetDirection;
};
