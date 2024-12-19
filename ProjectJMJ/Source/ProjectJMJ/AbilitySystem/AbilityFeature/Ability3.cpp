// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability3.h"
#include "ProjectJMJ/DataAsset/AbilityDataAsset.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"

void UAbility3::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (AbilityDataAsset && AbilityDataAsset->Action && ActorInfo->OwnerActor->GetWorld()) {
		ACharacter* Character = Cast<ACharacter>(ActorInfo->OwnerActor);

		if (AbilityDataAsset->AnimMontage.Num() > 0) {
			AnimInstace->Montage_Play(AbilityDataAsset->AnimMontage[0],1.5f);
		}

		FTimerHandle handle;
		ActorInfo->OwnerActor->GetWorldTimerManager().SetTimer(handle,[Character,ActorInfo,this]() {
			FTransform Transform;
			FVector v;
			if (Character) {
				v = Character->GetMesh()->GetSocketLocation(FName("hand_L"));
			}
			//FVector v = ActorInfo->OwnerActor->GetActorLocation() + (ActorInfo->OwnerActor->GetActorRotation().Vector() * 150);
			FRotator r;
			UCameraComponent* Camera = ActorInfo->OwnerActor->GetComponentByClass<UCameraComponent>();
			if (Camera) {
				r = Camera->K2_GetComponentRotation();
			}
			Transform.SetLocation(v);
			Transform.SetRotation(r.Quaternion());
			//Transform.SetLocation();
			AActor* actor = ActorInfo->OwnerActor->GetWorld()->SpawnActor(AbilityDataAsset->Action, &Transform);
			actor->SetLifeSpan(2);
			}, 1.0f, false, 1.0f);

		
	}
}
