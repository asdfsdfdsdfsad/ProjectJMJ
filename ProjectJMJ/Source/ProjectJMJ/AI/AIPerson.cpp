// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPerson.h"
#include "ProjectJMJ/Character/Component/AttributeComponent.h"
#include "ProjectJMJ/AbilitySystem/PersonAbilitySystemComponent.h"
#include "ProjectJMJ/Character/Component/WeaponComponent.h"

// Sets default values
AAIPerson::AAIPerson()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComp"));
	PersonAbilitySystemComponent = CreateDefaultSubobject<UPersonAbilitySystemComponent>(TEXT("AbilitySystem"));
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComp"));

	WeaponComponent->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,FName("Weapon"));
}

// Called when the game starts or when spawned
void AAIPerson::BeginPlay()
{
	Super::BeginPlay();
	if(!AttributeComponent->OnDeath.IsBound())
	AttributeComponent->OnDeath.BindUObject(this,&ThisClass::Death);
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this,&ThisClass::MontageEnd);
	GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this,&ThisClass::MontageNotifyBegin);
}

// Called every frame
void AAIPerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIPerson::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIPerson::Death(FVector Vector)
{
	//FGameplayEventData GameplayEventData;
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->AddImpulse(Vector*-50);
	
	//PersonAbilitySystemComponent->TryActivateAbilitiesByTag();
	//PersonAbilitySystemComponent->TryActivateAbilitiesByTag(UGameplayTagsManager::Get().RequestGameplayTagParents(FGameplayTag::RequestGameplayTag(FName("AbilityTag.Death"))));
	//GetMesh()->SetSimulatePhysics(true);
}

void AAIPerson::MontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	WeaponComponent->EmptyIgnoreActor();
	//Montage->GetName();
}

void AAIPerson::MontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	switch(NotifyName.GetNumber())
	{
	case 1:
		WeaponComponent->SetGenerateOverlapEvents(true);
		break;
	case 2:
		WeaponComponent->SetGenerateOverlapEvents(false);
		break;
	}
}

