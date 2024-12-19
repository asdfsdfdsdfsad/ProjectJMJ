// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIPerson.generated.h"

class UAttributeComponent;
class UPersonAbilitySystemComponent;
class UWeaponComponent;

UCLASS()
class PROJECTJMJ_API AAIPerson : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIPerson();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "UI");
	//TObjectPtr<UWidgetComponent> WidgetComponent;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Death(FVector Vector);

	UFUNCTION()
	void MontageEnd(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
	void MontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeComponent> AttributeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UPersonAbilitySystemComponent> PersonAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UWeaponComponent> WeaponComponent;
};
