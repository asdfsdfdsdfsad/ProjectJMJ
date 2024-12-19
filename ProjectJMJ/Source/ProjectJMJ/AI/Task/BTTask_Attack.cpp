// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ProjectJMJ/AI/Component/AIAttackComponent.h"
EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UAIAttackComponent* AttackComp=OwnerComp.GetAIOwner()->GetComponentByClass<UAIAttackComponent>();
	ACharacter* Character = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	if (AttackComp&&Character)
	{   
		AttackComp->TriggerAbility(Character);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
