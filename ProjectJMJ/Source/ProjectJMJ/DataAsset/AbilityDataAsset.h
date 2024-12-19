// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagsManager.h"
#include "AbilityDataAsset.generated.h"

class UAnimMontage;
class UInputAction;
/**
 * 
 */
UCLASS()
class PROJECTJMJ_API UAbilityDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly,Category="Input")
	UInputAction* InputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	TArray<TObjectPtr<UAnimMontage>> AnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Tag")
	FGameplayTag MontageEndTag;

	UPROPERTY(EditDefaultsOnly, Category = "Tag")
	FGameplayTag ActivateTag;

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	TSubclassOf<AActor> Action;

};
