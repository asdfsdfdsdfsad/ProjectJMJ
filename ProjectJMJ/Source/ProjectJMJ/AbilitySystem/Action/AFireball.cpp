// Fill out your copyright notice in the Description page of Project Settings.


#include "AFireball.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectJMJ/Character/Component/AttributeComponent.h"
// Sets default values
AAFireball::AAFireball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComp"));
	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMoveComp"));
	Niagara->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
	SphereComponent->AttachToComponent(Niagara,FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AAFireball::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::BoxBeginStartOverride);
}

// Called every frame
void AAFireball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAFireball::BoxBeginStartOverride(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (SweepResult.HitObjectHandle) {
		UAttributeComponent* AttrComp = SweepResult.GetActor()->GetComponentByClass<UAttributeComponent>();
		if (AttrComp) {
			AttrComp->ApplyDamages(SweepResult.GetActor(), AttrComp, -10, 0,true,GetActorRotation().Vector());
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Fire"));
		}
	}
}

