// Fill out your copyright notice in the Description page of Project Settings.


#include "AFlyingSword.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectJMJ/Character/Component/AttributeComponent.h"

// Sets default values
AAFlyingSword::AAFlyingSword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMoveComp"));
	BoxComponent->AttachToComponent(Niagara,FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AAFlyingSword::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::BoxBeginStartOverride);
	
}

// Called every frame
void AAFlyingSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAFlyingSword::SetNiagaraRotation(FVector v)
{
	if (Niagara)
	{
		Niagara->SetVariableVec3(FName("Rotation"), v);
		//BoxComponent->
		//Niagara->SetVariableVec3();
	}

}

void AAFlyingSword::SetActiveProjectile(bool b)
{
	ProjectileMovementComponent->Activate(b);
}

void AAFlyingSword::BoxBeginStartOverride(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (SweepResult.HitObjectHandle) {
		UAttributeComponent* AttrComp = SweepResult.GetActor()->GetComponentByClass<UAttributeComponent>();
		if (AttrComp) {
			AttrComp->ApplyDamages(SweepResult.GetActor(),AttrComp,-20,0,false,FVector(0.0f,0.0f,0.0f));
		}
	}
}

