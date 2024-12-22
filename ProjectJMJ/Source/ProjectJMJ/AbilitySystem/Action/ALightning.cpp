// Fill out your copyright notice in the Description page of Project Settings.


#include "ALightning.h"
#include "NiagaraComponent.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProjectJMJ/Character/Component/AttributeComponent.h"
#include "Components/BoxComponent.h"
// Sets default values
AALightning::AALightning()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->AttachToComponent(Niagara, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AALightning::BeginPlay()
{
	Super::BeginPlay();
	//FTimerHandle Handle;
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::BoxBeginStartOverride);
	//GetWorldTimerManager().SetTimer(Handle,this,&ThisClass::Active, 1.0f, false,0.9f);
}

// Called every frame
void AALightning::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Active();
}

void AALightning::Active()
{
	TArray<FVector> vList = UNiagaraDataInterfaceArrayFunctionLibrary::GetNiagaraArrayPosition(Niagara, FName("PositionUser"));
	TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;
	TArray<FVector> HitList;
	//for (int i = 0; i < vList.Num(); i += 2) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,FString::Printf(TEXT("%s"),*vList[i].ToString()));
		//FVector StartV = UKismetMathLibrary::TransformLocation(Niagara->GetComponentToWorld(), vList[i]);
		//if (i + 1 >= vList.Num())break;
		//FVector EndV = UKismetMathLibrary::TransformLocation(Niagara->GetComponentToWorld(), vList[i + 1]);
		//UKismetSystemLibrary::LineTraceSingleByProfile(GetWorld(), StartV, EndV, FName(), false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true, FLinearColor::Red, FLinearColor::Green, 0.0f);
		
	FVector StartV =this->GetOwner()->GetActorLocation();
	FVector EndV = StartV*FVector(1.0f,1.0f,0.0f);
	ActorsToIgnore.Add(GetOwner());
	UKismetSystemLibrary::BoxTraceSingle(GetWorld(), StartV, EndV,FVector(2.0f,2.0f,2.0f),FRotator(),ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Red, FLinearColor::Green, 2.0f);
		if (HitResult.bBlockingHit) {
			HitList.Add(HitResult.Location);
			UAttributeComponent* AttributeComp = HitResult.GetActor()->GetComponentByClass<UAttributeComponent>();
			if (AttributeComp) {
				AttributeComp->ApplyDamages(HitResult.GetActor(), AttributeComp, -20, 0.0f, false, FVector(0.0f, 0.0f, 0.0f));
			}
		}
	//}
	//Niagara->SetVariableInt(FName("CollisionCount"), HitList.Num());
	//UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(Niagara, FName("CollisionPosi"), HitList);
}

void AALightning::BoxBeginStartOverride(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (SweepResult.HitObjectHandle) {
		UAttributeComponent* AttrComp = SweepResult.GetActor()->GetComponentByClass<UAttributeComponent>();
		if (AttrComp) {
			AttrComp->ApplyDamages(SweepResult.GetActor(), AttrComp, -20, 0, false, FVector(0.0f, 0.0f, 0.0f));
		}
	}
}

