// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

DECLARE_DELEGATE_OneParam(FOnDeath,FVector);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnHealthChanged, AActor*, InstigatorActor, UAttributeComponent*, OwningComp, float, Damage, float, Delta, FVector, HitLocation);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTJMJ_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void SetHealth(float Value);

	UFUNCTION()
	float GetHealth();

	UFUNCTION()
	bool Death(FVector Vector);

	UFUNCTION()
	void ApplyDamages(AActor* InstigatorActor,UAttributeComponent* OwningComp, float Damage, float Delta,bool IsStrike,FVector HitLocation);

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	FOnDeath OnDeath;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, Category = "Attribute")
	float Health=100.0f;
};
