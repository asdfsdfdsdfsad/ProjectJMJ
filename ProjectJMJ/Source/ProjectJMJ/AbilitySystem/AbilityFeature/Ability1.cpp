// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability1.h"
#include "ProjectJMJ/DataAsset/AbilityDataAsset.h"
#include "Camera/CameraComponent.h"
#include "ProjectJMJ/AbilitySystem/Action/AFlyingSword.h"

void UAbility1::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (AbilityDataAsset&&AbilityDataAsset->Action && ActorInfo->OwnerActor->GetWorld()) {
		FTransform Transform;
		FVector v = ActorInfo->OwnerActor->GetActorLocation()+ (ActorInfo->OwnerActor->GetActorRotation().Vector()*100);
		FRotator r;
		UCameraComponent* Camera = ActorInfo->OwnerActor->GetComponentByClass<UCameraComponent>();
		if (Camera) {
			r = Camera->K2_GetComponentRotation();
		}
		Transform.SetLocation(v);
		Transform.SetRotation(r.Quaternion());
		//Transform.SetLocation();
		AActor* actor=ActorInfo->OwnerActor->GetWorld()->SpawnActor(AbilityDataAsset->Action,&Transform);
		AAFlyingSword* FlyingSword = Cast<AAFlyingSword>(actor);
		FlyingSword->SetLifeSpan(4);

		if (AbilityDataAsset->AnimMontage.Num()>0) {
			AnimInstace->Montage_Play(AbilityDataAsset->AnimMontage[0]);
		}
		
		if (FlyingSword) {
			FlyingSword->SetNiagaraRotation(ActorInfo->OwnerActor->GetActorRotation().Vector());
			FTimerHandle handle;
			ActorInfo->OwnerActor->GetWorldTimerManager().SetTimer(handle,[FlyingSword](){
			FlyingSword->SetActiveProjectile(true);
			},2.0f,false);
			
		}
	}

}
