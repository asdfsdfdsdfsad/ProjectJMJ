// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIPersonController.generated.h"

class UAIPerceptionComponent;
class UAIAttackComponent;
/**
 * 
 */
UCLASS()
class PROJECTJMJ_API AAIPersonController : public AAIController
{
	GENERATED_BODY()
public:
	AAIPersonController();

	virtual void BeginPlay() override;

	UFUNCTION()
	void PerceivedTarget(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UAIAttackComponent> AIAttackComponent;
};
