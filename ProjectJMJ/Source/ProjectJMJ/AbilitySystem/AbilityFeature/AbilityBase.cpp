// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityBase.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ProjectJMJ/DataAsset/AbilityDataAsset.h"
#include "GameplayTagsManager.h"

void UAbilityBase::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	if (Spec.GameplayEventData->OptionalObject)
		AbilityDataAsset = Cast<UAbilityDataAsset>(ActorInfo->AbilitySystemComponent->FindAbilitySpecFromHandle(Spec.Handle)->GameplayEventData->OptionalObject);
	AnimInstace = ActorInfo->SkeletalMeshComponent->GetAnimInstance();
	ActorInfos = ActorInfo;
	AbilityTags.AddTag(AbilityDataAsset->MontageEndTag);
	InstancingPolicy = EGameplayAbilityInstancingPolicy::NonInstanced;
}

void UAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{

}

void UAbilityBase::PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{

}

void UAbilityBase::EndAbilitys()
{

}

void UAbilityBase::MontageEnd(UAnimMontage* Montage, bool bInterrupted)
{

}
