// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TargetLocation.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
EBTNodeResult::Type UBTTask_TargetLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* Target=Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	if (Target)
	{
		FVector v = Target->GetActorLocation();
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),v);
		return EBTNodeResult::Succeeded;
	}
	//OwnerComp.GetOwner().try
	//FVector StartLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
	//FVector Direction = (TargetLocation - StartLocation).GetSafeNormal2D();
	//TargetLocation = TargetLocation - (Direction * AttackDistance);
	
	return EBTNodeResult::Failed;
}
