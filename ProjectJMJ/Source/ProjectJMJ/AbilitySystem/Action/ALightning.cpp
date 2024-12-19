// Fill out your copyright notice in the Description page of Project Settings.


#include "ALightning.h"
#include "NiagaraComponent.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectJMJ/Character/Component/AttributeComponent.h"
// Sets default values
AALightning::AALightning()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
}

// Called when the game starts or when spawned
void AALightning::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle,this,&ThisClass::Active, 1.0f, false,1.6f);
}

// Called every frame
void AALightning::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AALightning::Active()
{
	TArray<FVector> vList = UNiagaraDataInterfaceArrayFunctionLibrary::GetNiagaraArrayPosition(Niagara, FName("PositionUser"));
	TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;
	TArray<FVector> HitList;
	for (int i = 0; i < vList.Num(); i += 2) {
		FVector StartV = UKismetMathLibrary::TransformLocation(Niagara->K2_GetComponentToWorld(), vList[i]);
		if (i + 1 >= vList.Num())break;
		FVector EndV = UKismetMathLibrary::TransformLocation(Niagara->K2_GetComponentToWorld(), vList[i + 1]);
		UKismetSystemLibrary::LineTraceSingleByProfile(GetWorld(), StartV, EndV, FName(), false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true, FLinearColor::Red, FLinearColor::Green, 0.0f);
		if (HitResult.bBlockingHit) {
			HitList.Add(HitResult.Location);
			UAttributeComponent* AttributeComp = HitResult.GetActor()->GetComponentByClass<UAttributeComponent>();
			if (AttributeComp) {
				AttributeComp->ApplyDamages(HitResult.GetActor(), AttributeComp, -20, 0.0f, false, FVector(0.0f, 0.0f, 0.0f));
			}
		}
	}
	Niagara->SetVariableInt(FName("CollisionCount"), HitList.Num());
	UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(Niagara, FName("CollisionPosi"), HitList);
}

