// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DeathAbility.generated.h"
class UAbilityDataAsset;
class UAnimInstance;
/**
 * 
 */
UCLASS()
class PROJECTJMJ_API UDeathAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UDeathAbility();

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	/** Actually activate ability, do not call this directly */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData = nullptr) override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<const UAbilityDataAsset> AbilityDataAsset;

	const FGameplayAbilityActorInfo* ActorInfos;

	UFUNCTION()
	void MontageEnd(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY()
	UAnimInstance* AnimInstance;
};
