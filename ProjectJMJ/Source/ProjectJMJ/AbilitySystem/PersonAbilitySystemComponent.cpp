// Fill out your copyright notice in the Description page of Project Settings.

#include "PersonAbilitySystemComponent.h"
#include "ProjectJMJ/Character/Component/PlayerControlComponent.h"

void UPersonAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
	InitAbility();
}

void UPersonAbilitySystemComponent::AddAbility(TSubclassOf<UGameplayAbility> AbilityType)
{
	FGameplayAbilitySpecHandle AbilityHandle;
	if (AbilityType)
	{
		FGameplayAbilitySpec AbilitySpec(AbilityType);
		//AbilitySpec.RemoveAfterActivation = true;
		AbilityHandle = GiveAbility(AbilitySpec);
		if (AbilityHandle.IsValid() && !AbilityHandleArray.Contains(AbilityHandle))
		{
			AbilityHandleArray.Add(AbilityHandle);
		}
	}
}

void UPersonAbilitySystemComponent::ActivatonAbility()
{
	if(!AbilityHandleArray.IsEmpty())
	TryActivateAbility(AbilityHandleArray[0]);
}

void UPersonAbilitySystemComponent::InitAbility()
{
	for (int i = 0; i < AbilityAsset.Num(); i++) {
		if (AbilityAsset[i].Ability)
		{
			FGameplayAbilitySpecHandle AbilityHandle;
			FGameplayAbilitySpec AbilitySpec(AbilityAsset[i].Ability);
			TSharedPtr<FGameplayEventData> GameplayEventData = MakeShared<FGameplayEventData>();
			GameplayEventData->OptionalObject = AbilityAsset[i].AbilityDataAsset;
			AbilitySpec.GameplayEventData = GameplayEventData;
			AbilitySpec.Ability->AbilityTags.AddTag(AbilityAsset[i].AbilityDataAsset->ActivateTag);
			AbilityHandle = GiveAbility(AbilitySpec);
			if (AbilityHandle.IsValid() && !AbilityHandleArray.Contains(AbilityHandle))
			{
				if(AbilityAsset[i].AbilityDataAsset->InputAction)
				InputActions.Add(AbilityAsset[i].AbilityDataAsset->InputAction);
				AbilityHandleArray.Add(AbilityHandle);
			}
		}
	}
	if(InputActions.Num()>0)
	BindAbilityInput();
}

void UPersonAbilitySystemComponent::AbilityInputBindPressed(const FInputActionValue& InputActionValue,FGameplayAbilitySpecHandle Handle)
{
	float a=InputActionValue.Get<FInputActionValue::Axis1D>();
    FindAbilitySpecFromHandle(Handle)->InputID=a;
	TryActivateAbility(Handle);
}

void UPersonAbilitySystemComponent::BindAbilityInput()
{
	UPlayerControlComponent* PlayerControlComponent = GetOwner()->GetComponentByClass<UPlayerControlComponent>();
	if (PlayerControlComponent) {
		for (int i = 0; i < InputActions.Num();i++){
			if (i<AbilityHandleArray.Num()) {
				PlayerControlComponent->BindInputAction(InputActions[i], ETriggerEvent::Triggered, this, &ThisClass::AbilityInputBindPressed, AbilityHandleArray[i]);
			}	
		}
	}
}
