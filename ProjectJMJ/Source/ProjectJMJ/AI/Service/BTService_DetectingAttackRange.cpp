// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DetectingAttackRange.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
void UBTService_DetectingAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);
	FVector StartV = OwnerComp.GetAIOwner()->GetPawn()->GetTargetLocation();
	FVector EndV = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TargetLocation.SelectedKeyName);
	float dis = 0.0f;
	dis=FVector::Distance(StartV,EndV);
	float range = 0.0f;
	range=OwnerComp.GetBlackboardComponent()->GetValueAsFloat(AttackRange.SelectedKeyName);
	bool b = false;
	if(range>dis)
	{
		b = true;
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString("true"));
		}
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsAttack.SelectedKeyName,b);
}
