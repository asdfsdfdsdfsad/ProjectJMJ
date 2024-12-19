// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPersonController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "ProjectJMJ/AI/Component/AIAttackComponent.h"

AAIPersonController::AAIPersonController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComp"));
	AIAttackComponent = CreateDefaultSubobject<UAIAttackComponent>(TEXT("AIAttackComp"));
}

void AAIPersonController::BeginPlay()
{
	Super::BeginPlay();
	//RunBehaviorTree();
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::PerceivedTarget);
}

void AAIPersonController::PerceivedTarget(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor->Tags.Num() > 0 && Actor->Tags[0].IsEqual(FName("Person"))) 
	{
		if (Stimulus.WasSuccessfullySensed()) 
		{
			GetBlackboardComponent()->SetValueAsBool(FName("isFindTarget"), true);
			GetBlackboardComponent()->SetValueAsObject(FName("TargetActor"),Actor);
		}
		else {
			GetBlackboardComponent()->SetValueAsBool(FName("isFindTarget"),false);
		}
	}

}
