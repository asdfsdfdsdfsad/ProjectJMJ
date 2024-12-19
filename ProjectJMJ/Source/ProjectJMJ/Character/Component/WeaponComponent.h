// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "WeaponComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (Rendering, Common), hidecategories = (Object, Activation, "Components|Activation"), ShowCategories = (Mobility), editinlinenew, meta = (BlueprintSpawnableComponent))
class PROJECTJMJ_API UWeaponComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
private:
	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void DelayExeFunc();

	UPROPERTY()
	USkeletalMeshComponent* MeshComp;

	UPROPERTY()
	TArray<AActor*> IgnoreActor;

	UPROPERTY(EditAnywhere, Category = "Attribute")
	float Attack = -20.0f;
public:
	UFUNCTION()
	void EmptyIgnoreActor();
};
