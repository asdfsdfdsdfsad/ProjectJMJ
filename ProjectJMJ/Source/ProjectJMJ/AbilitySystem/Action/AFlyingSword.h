// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AFlyingSword.generated.h"

class UNiagaraComponent;
class UBoxComponent;
class UProjectileMovementComponent;
UCLASS()
class PROJECTJMJ_API AAFlyingSword : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAFlyingSword();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetNiagaraRotation(FVector v);

	UFUNCTION()
	void SetActiveProjectile(bool b);

	UFUNCTION()
	void BoxBeginStartOverride(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraComponent> Niagara;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> BoxComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
};
