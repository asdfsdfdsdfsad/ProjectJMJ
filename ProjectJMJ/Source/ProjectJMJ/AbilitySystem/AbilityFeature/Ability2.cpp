// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability2.h"
#include "ProjectJMJ/DataAsset/AbilityDataAsset.h"

void UAbility2::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (AbilityDataAsset && AbilityDataAsset->Action && ActorInfo->OwnerActor->GetWorld()) {
		FTransform Transform;
		FVector v = ActorInfo->OwnerActor->GetActorLocation() + (ActorInfo->OwnerActor->GetActorRotation().Vector() * 200)+FVector(0.0f,0.0f,800.0f);
		FRotator r;
		//UCameraComponent* Camera = ActorInfo->OwnerActor->GetComponentByClass<UCameraComponent>();
		//if (Camera) {
		//	r = Camera->K2_GetComponentRotation();
		//}
		Transform.SetLocation(v);
		Transform.SetRotation(r.Quaternion());
		//Transform.SetLocation();
		//AbilityDataAsset->AnimMontage[0]->ONni
		if (AbilityDataAsset->AnimMontage.Num() > 0) {
			AnimInstace->Montage_Play(AbilityDataAsset->AnimMontage[0],2.0f);
		}
		AActor* actor = ActorInfo->OwnerActor->GetWorld()->SpawnActor(AbilityDataAsset->Action, &Transform);
		actor->SetLifeSpan(2);
	}
}
