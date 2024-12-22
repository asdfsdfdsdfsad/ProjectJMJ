// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability1.h"
#include "ProjectJMJ/DataAsset/AbilityDataAsset.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectJMJ/AbilitySystem/Action/AFlyingSword.h"
#include <Kismet/KismetSystemLibrary.h>

void UAbility1::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (AbilityDataAsset&&AbilityDataAsset->Action && ActorInfo->OwnerActor->GetWorld()) {
		FTransform Transform;
		FVector v = ActorInfo->OwnerActor->GetActorLocation()+ (ActorInfo->OwnerActor->GetActorRotation().Vector()*100);
		FRotator r;
		UCameraComponent* Camera = ActorInfo->OwnerActor->GetComponentByClass<UCameraComponent>();
		FVector  StartV;
		FVector EndV;
		FRotator rs;
		if (Camera) {
			TArray<AActor*> ActorsToIgnore;
			ActorsToIgnore.Add(ActorInfo->OwnerActor.Get());
			FHitResult Result;
			ActorInfo->OwnerActor->GetActorEyesViewPoint(StartV, rs);
			EndV = (Camera->GetComponentLocation() + (Camera->K2_GetComponentRotation().Vector() * 2000));
			if (ActorInfo->OwnerActor->GetWorld())
			{
				UKismetSystemLibrary::LineTraceSingle(ActorInfo->OwnerActor->GetWorld(), Camera->GetComponentLocation(), EndV, ETraceTypeQuery::TraceTypeQuery3, false, ActorsToIgnore, EDrawDebugTrace::Type::None, Result, true, FLinearColor::Red, FLinearColor::Green, 2.0f);
			}
			r = UKismetMathLibrary::FindLookAtRotation(StartV, EndV);
			if (Result.bBlockingHit) {
				r = UKismetMathLibrary::FindLookAtRotation(StartV, Result.Location);
			}
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
