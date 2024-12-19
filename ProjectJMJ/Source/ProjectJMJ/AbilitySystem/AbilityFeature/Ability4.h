// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityBase.h"
#include "Ability4.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJMJ_API UAbility4 : public UAbilityBase
{
	GENERATED_BODY()
public:
	/** Actually activate ability, do not call this directly */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

};
