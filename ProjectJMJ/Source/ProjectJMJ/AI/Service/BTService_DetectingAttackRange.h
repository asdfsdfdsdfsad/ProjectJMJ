// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_DetectingAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJMJ_API UBTService_DetectingAttackRange : public UBTService_BlueprintBase
{
	GENERATED_BODY()
public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Set AI")
	FBlackboardKeySelector TargetLocation;
	UPROPERTY(EditAnywhere, Category = "Set AI")
	FBlackboardKeySelector AttackRange;
	UPROPERTY(EditAnywhere, Category = "Out AI")
	FBlackboardKeySelector IsAttack;
};
