// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectJMJ/Character/Component/PlayerControlComponent.h"
#include "PersonControlsComponent.generated.h"

UENUM(BlueprintType)
enum class Gait :uint8 {
	Walk UMETA(DisplayName = "Walk"),
	Run UMETA(DisplayName = "Run"),
	Sprint UMETA(DisplayName = "Sprint"),
};
/**
 * 
 */
UCLASS(Blueprintable,BlueprintType,Category="Input",meta=(BlueprintSpawnableComponent))
class PROJECTJMJ_API UPersonControlsComponent : public UPlayerControlComponent
{
	GENERATED_BODY()
	
public:
	UPersonControlsComponent();

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Gait")
	Gait gait;
protected:
	virtual void AddPlayerControls_Implementation(UEnhancedInputComponent* PlayerInputComponent) override;
    
	void MoveForward(const FInputActionValue& InputActionValue);
	void MoveRight(const FInputActionValue& InputActionValue);
	void MoveUp(const FInputActionValue& InputActionValue);
	void Turn(const FInputActionValue& InputActionValue);
	void LookUp(const FInputActionValue& InputActionValue);
	void StartTurbo(const FInputActionValue& InputActionValue);
	void StopTurbo(const FInputActionValue& InputActionValue);
	void Jump(const FInputActionValue& InputActionValue);
	void Walk(const FInputActionValue& InputActionValue);
	void StartSprint(const FInputActionValue& InputActionValue);
	void EndSprint(const FInputActionValue& InputActionValue);

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="PlayerControls")
	UInputAction* MoveForwardInput;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="PlayerControls")
	UInputAction* MoveRightInput;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="PlayerControls")
	UInputAction* MoveUpInput;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="PlayerControls")
	UInputAction* TurnInput;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerControls")
	UInputAction* LookUpInput;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="PlayerControls")
	UInputAction* TurboInput;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="PlayerControls")
	UInputAction* JumpInput;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerControls")
	UInputAction* WalkInput;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerControls")
	UInputAction* SprintInput;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="IsMove")
	bool IsMove=true;
};
