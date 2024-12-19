// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability4.h"
#include "ProjectJMJ/DataAsset/AbilityDataAsset.h"
#include "ProjectJMJ/AbilitySystem/Action/Aice.h"
void UAbility4::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (AbilityDataAsset && AbilityDataAsset->Action && ActorInfo->OwnerActor->GetWorld()) {
		FTransform Transform;
		FVector v = ActorInfo->OwnerActor->GetActorLocation() + (ActorInfo->OwnerActor->GetActorRotation().Vector() * 150)+FVector(0.0f,0.0f,-80.0f);
		FRotator r= ActorInfo->OwnerActor->GetActorRotation();
		//UCameraComponent* Camera = ActorInfo->OwnerActor->GetComponentByClass<UCameraComponent>();
		//if (Camera) {
		//	r = Camera->K2_GetComponentRotation();
		//}
		Transform.SetLocation(v);
		Transform.SetRotation(r.Quaternion());
		if (AbilityDataAsset->AnimMontage.Num() > 0) {
			AnimInstace->Montage_Play(AbilityDataAsset->AnimMontage[0], 4.0f);
		}
		//Transform.SetLocation();
		AActor* actor = ActorInfo->OwnerActor->GetWorld()->SpawnActor(AbilityDataAsset->Action, &Transform);
		if (actor) {
			AAice* aaice = Cast<AAice>(actor);
			if (aaice)
			{
				aaice->TriggerDamage();
			}
			actor->SetLifeSpan(5);
		}
		
	}
}
