// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AIAbilityPerson.generated.h"

/**
 * 
 */
UCLASS(config = Game, BlueprintType, Blueprintable, hideCategories = (Navigation))
class PROJECTJMJ_API UAIAbilityPerson : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void TriggerAbility(ACharacter* Character,UAnimMontage* AnimMontage);
	
};
