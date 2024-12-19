// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AttributeComponent.h"

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	OnComponentBeginOverlap.AddDynamic(this,&ThisClass::BeginOverlap);
	IgnoreActorWhenMoving(GetOwner(), true);
	SetGenerateOverlapEvents(false);
}

void UWeaponComponent::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IgnoreActor.Contains(SweepResult.GetActor()))
	{
		IgnoreActor.Add(SweepResult.GetActor());
		if (SweepResult.HitObjectHandle)
		{
			TArray<AActor*> ActorsToIgnore;
			ActorsToIgnore.Add(GetOwner());
			FHitResult HitResult;
			UKismetSystemLibrary::SphereTraceSingle(GetWorld(), OverlappedComponent->GetComponentLocation(), SweepResult.HitObjectHandle.GetLocation(), 5.0f, ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true);

			if (HitResult.bBlockingHit) {
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attack"));
				MeshComp = Cast<USkeletalMeshComponent>(HitResult.GetComponent());
				if (MeshComp) {
					MeshComp->SetBodySimulatePhysics(HitResult.BoneName, true);
					MeshComp->SetAllBodiesBelowSimulatePhysics(HitResult.BoneName, true);
					//MeshComp->AddImpulseToAllBodiesBelow(HitResult.ImpactNormal * -100, HitResult.BoneName);
					FLatentActionInfo LatentInfo;
					LatentInfo.Linkage = 0;
					LatentInfo.UUID = __LINE__;
					LatentInfo.ExecutionFunction = FName(TEXT("DelayExeFunc"));
					LatentInfo.CallbackTarget = this;
					UAttributeComponent* AttriComp = HitResult.GetActor()->GetComponentByClass<UAttributeComponent>();
					if (AttriComp) {
						AttriComp->ApplyDamages(OtherActor, nullptr, Attack, 0.0f,false,HitResult.Location);
						if (AttriComp->GetHealth()>0)
						{
							UKismetSystemLibrary::Delay(GetWorld(), 0.1f, LatentInfo);
						}
					}
					
				}

			}
		}
	}
}

void UWeaponComponent::DelayExeFunc()
{
	if (MeshComp) {
		MeshComp->SetSimulatePhysics(false);
	}
}

void UWeaponComponent::EmptyIgnoreActor()
{
	SetGenerateOverlapEvents(false);
	IgnoreActor.Empty();
}
