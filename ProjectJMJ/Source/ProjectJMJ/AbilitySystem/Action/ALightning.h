// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ALightning.generated.h"

class UNiagaraComponent;
UCLASS()
class PROJECTJMJ_API AALightning : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AALightning();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Active();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraComponent> Niagara;
};
