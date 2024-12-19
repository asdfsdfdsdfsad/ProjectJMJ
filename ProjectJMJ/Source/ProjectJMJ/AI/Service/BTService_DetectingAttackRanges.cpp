// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DetectingAttackRanges.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ProjectJMJ/Character/Person.h"

void UBTService_DetectingAttackRanges::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	APerson* obj =Cast<APerson>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Target.SelectedKeyName));
	bool b = false;
	if (obj) 
	{
		FVector StartV = OwnerComp.GetAIOwner()->GetPawn()->GetTargetLocation();
		FVector EndV = obj->GetActorLocation();
		float dis = FVector::Distance(StartV, EndV);
		float range = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(AttackRange.SelectedKeyName);
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetDirection.SelectedKeyName, EndV);
		if (range >= dis)
		{
			b = true;
			/*if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Target: %s"),*EndV.ToString()));
			}*/
		}
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsAttack.SelectedKeyName, b);
	/*if (GEngine) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Target: %d"),b));
	}*/
}
