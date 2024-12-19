// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalAttackAbility.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayTagsManager.h"
#include "ProjectJMJ/Character/Component/WeaponComponent.h"

UNormalAttackAbility::UNormalAttackAbility()
{

}

void UNormalAttackAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo,Spec);
	if(Spec.GameplayEventData->OptionalObject)
	AbilityDataAsset = Cast<UAbilityDataAsset>(ActorInfo->AbilitySystemComponent->FindAbilitySpecFromHandle(Spec.Handle)->GameplayEventData->OptionalObject);
	AnimInstace = ActorInfo->SkeletalMeshComponent->GetAnimInstance();
	ActorInfos = ActorInfo;
	AbilityTags.AddTag(AbilityDataAsset->MontageEndTag);
	InstancingPolicy = EGameplayAbilityInstancingPolicy::NonInstanced;
	EndAbilitys();
}

void UNormalAttackAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (isStarting) return;
	isStarting = true;

	if (Handle.IsValid()) 
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on-screen debug message"));
		}
	}

	FGameplayAbilitySpec* Spec = ActorInfo->AbilitySystemComponent->FindAbilitySpecFromHandle(Handle);
	UCharacterMovementComponent* MoveComp = Cast<UCharacterMovementComponent>(ActorInfo->MovementComponent);
	if (AbilityDataAsset->AnimMontage.Num() >= 2) {
		AnimInstace->OnMontageEnded.AddDynamic(this,&ThisClass::MontageEnd);
		AnimInstace->OnAllMontageInstancesEnded;
		if (Spec->InputID > 0 && !MoveComp->IsFalling())
		{
			AnimInstace->Montage_Play(AbilityDataAsset->AnimMontage[0], 2.0f);
		}
		else
		{
			if (MoveComp && MoveComp->IsFalling())
			{
				AnimInstace->Montage_Play(AbilityDataAsset->AnimMontage[2], 2.0f);
			}
			else
			{
				AnimInstace->Montage_Play(AbilityDataAsset->AnimMontage[1], 2.0f);
			}

		}
	}
	UWeaponComponent* Weapon = ActorInfo->OwnerActor->GetComponentByClass<UWeaponComponent>();
	if (Weapon)
	{
		Weapon->SetGenerateOverlapEvents(true);
	}
	
}

void UNormalAttackAbility::PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{
	//Super::PreActivate(Handle,ActorInfo,ActivationInfo,OnGameplayAbilityEndedDelegate,TriggerEventData);
	if (Handle.IsValid())
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PreActivate"));
		}
	}

	/*UCharacterMovementComponent* MoveComp=ActorInfo->OwnerActor->GetComponentByClass<UCharacterMovementComponent>();
	if (MoveComp&&!MoveComp->IsFalling())
	{
		MoveComp->SetMovementMode(EMovementMode::MOVE_None);
	}*/
}

void UNormalAttackAbility::EndAbilitys()
{
	isStarting = false;
	AnimInstace->OnMontageEnded.RemoveDynamic(this, &ThisClass::MontageEnd);
	UWeaponComponent* Weapon = ActorInfos->OwnerActor->GetComponentByClass<UWeaponComponent>();
	if (Weapon)
	{
		Weapon->EmptyIgnoreActor();
	}
}

void UNormalAttackAbility::MontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	if (AbilityDataAsset&&AbilityTags.HasTag(AbilityDataAsset->MontageEndTag))
	{
		EndAbilitys();
		UCharacterMovementComponent* MoveComp = ActorInfos->OwnerActor->GetComponentByClass<UCharacterMovementComponent>();
		if (MoveComp && !MoveComp->IsFalling())
		{
			MoveComp->SetMovementMode(EMovementMode::MOVE_Walking);
		}
	}
}
