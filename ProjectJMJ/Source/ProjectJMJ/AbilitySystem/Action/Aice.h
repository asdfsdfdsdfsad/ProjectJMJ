// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Aice.generated.h"
class UNiagaraComponent;

UCLASS()
class PROJECTJMJ_API AAice : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAice();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraComponent> Niagara;

	UPROPERTY()
	FTimerHandle Handle;

	UPROPERTY()
	FVector StartV;

	UFUNCTION()
	void TriggerDamage();
};
