// Fill out your copyright notice in the Description page of Project Settings.


#include "AIAttackComponent.h"
#include "ProjectJMJ/AI/Ability/AIAbilityPerson.h"

// Sets default values for this component's properties
UAIAttackComponent::UAIAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	AIAbilityPerson = NewObject<UAIAbilityPerson>();
	// ...
}


// Called when the game starts
void UAIAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAIAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAIAttackComponent::TriggerAbility(ACharacter* Character)
{
	if (AnimMontage)
	{
		AIAbilityPerson->TriggerAbility(Character,AnimMontage);
	}
}

