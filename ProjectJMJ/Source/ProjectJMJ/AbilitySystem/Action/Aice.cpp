// Fill out your copyright notice in the Description page of Project Settings.


#include "Aice.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectJMJ/Character/Component/AttributeComponent.h"
// Sets default values
AAice::AAice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
}

// Called when the game starts or when spawned
void AAice::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAice::TriggerDamage()
{
	//FTimerHandle Handle;
	StartV = GetActorLocation()+FVector(0.0f,0.0f,50.0f);
	GetWorldTimerManager().SetTimer(Handle, [this](){
		FVector v2 = StartV+(GetActorRotation().Vector()*200);
		TArray<AActor*> ActorsToIgnore;
		FHitResult HitResult;
		UKismetSystemLibrary::BoxTraceSingleByProfile(GetWorld(), StartV, v2, FVector(50.0f, 50.0f, 50.0f), FRotator(0.0f, 0.0f,0.0f),FName(""),false, ActorsToIgnore,EDrawDebugTrace::None,HitResult,true,FLinearColor::Red,FLinearColor::Green,2.0f);
		StartV = v2;
		if (HitResult.bBlockingHit) 
		{
			UAttributeComponent * AttrComp=HitResult.GetActor()->GetComponentByClass<UAttributeComponent>();
			if(AttrComp)
			AttrComp->ApplyDamages(HitResult.GetActor(),AttrComp,-20,1.0f,true,FVector(0.0f,0.0f,50.0f));
		}
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Test"));
		}
		},1.0f,true,0.0f);
	//GetWorldTimerManager().ClearTimer(Handle);
	FTimerHandle Handle2;
	GetWorldTimerManager().SetTimer(Handle2, [this](){
		if (GEngine&&GetWorldTimerManager().IsTimerActive(Handle)){
			GetWorldTimerManager().ClearTimer(Handle);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Clear Timer"));
			}
	},1.0f,false, 2.5f);
}

