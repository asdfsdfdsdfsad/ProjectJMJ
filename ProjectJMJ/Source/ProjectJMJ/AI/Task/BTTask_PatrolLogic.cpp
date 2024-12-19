// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PatrolLogic.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
EBTNodeResult::Type UBTTask_PatrolLogic::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UNavigationSystemV1* Nav=  UNavigationSystemV1::GetCurrent(GetWorld());
	if (Nav) {
		FVector v = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
		FNavLocation NavLocation;
		if (Nav->GetRandomPointInNavigableRadius(v, Radius, NavLocation))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), NavLocation);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
