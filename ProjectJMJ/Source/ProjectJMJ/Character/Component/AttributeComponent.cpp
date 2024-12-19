// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"
#include "GameFramework/Character.h"
// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UAttributeComponent::SetHealth(float Value)
{
	Health = Value;
}

float UAttributeComponent::GetHealth()
{
	return Health;
}

bool UAttributeComponent::Death(FVector Vector)
{
	if (Health <= 0&&OnDeath.IsBound())
	{
		OnDeath.Execute(Vector);
		return true;
	}
	return false;
}

void UAttributeComponent::ApplyDamages(AActor* InstigatorActor, UAttributeComponent* OwningComp, float Damage, float Delta, bool IsStrike,FVector HitLocation)
{
	Health += Damage;
	if (OnHealthChanged.IsBound()) {
		OnHealthChanged.Broadcast(InstigatorActor,this,Health,Delta,HitLocation);
	}
	if (IsStrike) 
	{
		ACharacter* Character = Cast<ACharacter>(InstigatorActor);
		if (Character) {
			Character->LaunchCharacter(HitLocation*20,true,true);
		}
	}
	if (Health<=0) 
	{
		Death(HitLocation);//GetOwner()->
	}
}

// Called every frame
void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

