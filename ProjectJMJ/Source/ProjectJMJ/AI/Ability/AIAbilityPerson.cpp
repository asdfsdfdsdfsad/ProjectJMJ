// Fill out your copyright notice in the Description page of Project Settings.


#include "AIAbilityPerson.h"
#include "GameFramework/Character.h"
#include "ProjectJMJ/Character/Component/WeaponComponent.h"
void UAIAbilityPerson::TriggerAbility(ACharacter* Character,UAnimMontage* AnimMontage)
{
	Character->PlayAnimMontage(AnimMontage);
}
