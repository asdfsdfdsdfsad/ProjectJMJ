// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "ProjectJMJ/DataAsset/AbilityDataAsset.h"
#include "PersonAbilitySystemComponent.generated.h"

class UGameplayAbility;
class UAbilityDataAsset; 

USTRUCT(BlueprintType)
struct FAbilityAsset {
	GENERATED_USTRUCT_BODY()
	FAbilityAsset() {}
	~FAbilityAsset() {}
public:
	UPROPERTY(EditDefaultsOnly, Category = "AbilitySystem")
	TSubclassOf<UGameplayAbility> Ability;

	UPROPERTY(EditDefaultsOnly, Category = "DataAsset")
	TObjectPtr<UAbilityDataAsset> AbilityDataAsset;
};
/**
 * 
 */
UCLASS()
class PROJECTJMJ_API UPersonAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	UFUNCTION()
	void AddAbility(TSubclassOf<UGameplayAbility> AbilityType);
	UFUNCTION()
	void ActivatonAbility();
	UFUNCTION()
	void InitAbility();

	UFUNCTION()
	void AbilityInputBindPressed(const FInputActionValue& InputActionValue,FGameplayAbilitySpecHandle Handle);

	UFUNCTION()
	void BindAbilityInput();

	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilityHandleArray;

	UPROPERTY()
	TArray<UInputAction *> InputActions;

	UPROPERTY(EditDefaultsOnly,Category="DataAsset")
 	TArray<FAbilityAsset> AbilityAsset;
};
