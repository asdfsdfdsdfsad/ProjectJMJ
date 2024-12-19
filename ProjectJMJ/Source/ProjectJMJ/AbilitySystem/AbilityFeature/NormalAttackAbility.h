// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ProjectJMJ/DataAsset/AbilityDataAsset.h"
#include "NormalAttackAbility.generated.h"
class UAbilityDataAsset;
struct FGameplayAbilityActorInfo;
/**
 * 
 */
UCLASS()
class PROJECTJMJ_API UNormalAttackAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UNormalAttackAbility();

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	/** Actually activate ability, do not call this directly */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData = nullptr) override;

	void EndAbilitys();

	UPROPERTY(EditAnywhere)
	TObjectPtr<const UAbilityDataAsset> AbilityDataAsset;

	const FGameplayAbilityActorInfo* ActorInfos;

	UFUNCTION()
	void MontageEnd(UAnimMontage* Montage, bool bInterrupted);

	UPROPERTY()
	UAnimInstance* AnimInstace;

	bool isStarting = false;
};
