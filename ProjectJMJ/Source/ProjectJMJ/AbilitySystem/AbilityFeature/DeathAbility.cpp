// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathAbility.h"
#include "AbilitySystemComponent.h"
#include "ProjectJMJ/DataAsset/AbilityDataAsset.h"

UDeathAbility::UDeathAbility()
{

}

void UDeathAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	if (Spec.GameplayEventData->OptionalObject)
	AbilityDataAsset = Cast<UAbilityDataAsset>(ActorInfo->AbilitySystemComponent->FindAbilitySpecFromHandle(Spec.Handle)->GameplayEventData->OptionalObject);
	AnimInstance = ActorInfo->SkeletalMeshComponent->GetAnimInstance();
	ActorInfos = ActorInfo;
	AbilityTags.AddTag(AbilityDataAsset->MontageEndTag);
	InstancingPolicy = EGameplayAbilityInstancingPolicy::NonInstanced;
}

void UDeathAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (AbilityDataAsset) {
		if(AbilityDataAsset->AnimMontage.Num()>0)
		ActorInfos->SkeletalMeshComponent->SetSimulatePhysics(true);
		ActorInfos->SkeletalMeshComponent->AddImpulse(FVector(100000.0f,0.0f,0.0f));
			//AnimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::MontageEnd);
			//AnimInstance->Montage_Play(AbilityDataAsset->AnimMontage[0]);
	}
}

void UDeathAbility::PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{

}

void UDeathAbility::MontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	if (AbilityDataAsset && AbilityTags.HasTag(AbilityDataAsset->MontageEndTag)) 
	{
		ActorInfos->SkeletalMeshComponent->SetSimulatePhysics(true);
		AnimInstance->OnMontageEnded.RemoveDynamic(this, &ThisClass::MontageEnd);
	}
}
