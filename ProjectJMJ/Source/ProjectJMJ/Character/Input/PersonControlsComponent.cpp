// Fill out your copyright notice in the Description page of Project Settings.

#include "PersonControlsComponent.h"
#include "Math/RotationMatrix.h"
#include "Math/Axis.h"

UPersonControlsComponent::UPersonControlsComponent()
{

}

void UPersonControlsComponent::AddPlayerControls_Implementation(UEnhancedInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	if(MoveForwardInput!=nullptr)
	BindInputAction(MoveForwardInput,ETriggerEvent::Triggered,this,&ThisClass::MoveForward);
	if(MoveRightInput!=nullptr)
	BindInputAction(MoveRightInput,ETriggerEvent::Triggered,this,&ThisClass::MoveRight);
	//BindInputAction(MoveUpInput,ETriggerEvent::Triggered,this,&ThisClass::MoveUp);
	if(TurnInput!=nullptr)
	BindInputAction(TurnInput,ETriggerEvent::Triggered,this,&ThisClass::Turn);
	if(LookUpInput!=nullptr)
	BindInputAction(LookUpInput,ETriggerEvent::Triggered,this,&ThisClass::LookUp);
	//BindInputAction(TurboInput,ETriggerEvent::Started,this,&ThisClass::StartTurbo);
	//BindInputAction(TurboInput,ETriggerEvent::Completed,this,&ThisClass::StopTurbo);
	if(JumpInput!=nullptr)
	BindInputAction(JumpInput,ETriggerEvent::Triggered,this,&ThisClass::Jump);
	if (WalkInput != nullptr)
	BindInputAction(WalkInput, ETriggerEvent::Triggered, this, &ThisClass::Walk);
	if (SprintInput != nullptr)
	{
		BindInputAction(SprintInput, ETriggerEvent::Started, this, &ThisClass::StartSprint);
		BindInputAction(SprintInput, ETriggerEvent::Completed, this, &ThisClass::EndSprint);
	}
}

void UPersonControlsComponent::MoveForward(const FInputActionValue& InputActionValue)
{
	if (Characters != nullptr) {
	float Val = InputActionValue.Get<FInputActionValue::Axis1D>();
	//获取控制器的旋转
	FRotator const Rotator = Characters->GetControlRotation();

	//获得向前的方向
	FVector Vector = FRotationMatrix(Rotator).GetScaledAxis(EAxis::X);
	Vector.Z = 0.f;
	if (Vector.IsZero() != true && IsMove) {
		//转换单位向量
		Vector.Normalize();
		float MassageVal = FMath::Square(Val);
		MassageVal = (Val < 0) ? -MassageVal : MassageVal;
		Characters->AddMovementInput(Vector, MassageVal);
	}
	}
}

void UPersonControlsComponent::MoveRight(const FInputActionValue& InputActionValue)
{

	if (Characters != nullptr)
	{
		float Val = InputActionValue.Get<FInputActionValue::Axis1D>();
		//获取控制器的旋转
		FRotator const Rotator = Characters->GetControlRotation();
		//获得向左的方向
		FVector Vector = FRotationMatrix(Rotator).GetScaledAxis(EAxis::Y);
		Vector.Z = 0.f;
		if (Vector.IsZero() != true&&IsMove) {
			//转换单位向量
			Vector.Normalize();
			float MassageVal = FMath::Square(Val);
			MassageVal = (Val < 0) ? -MassageVal : MassageVal;
			Characters->AddMovementInput(Vector, MassageVal);
		}
	}
}

void UPersonControlsComponent::MoveUp(const FInputActionValue& InputActionValue)
{
	if (Characters != nullptr) {
		float Val = InputActionValue.Get<FInputActionValue::Axis1D>();
		float MassageVal = FMath::Pow(FMath::Abs(Val), 3.0f);
		MassageVal = (Val < 0) ? -MassageVal : MassageVal;
		if (MassageVal != 0.f) {
			Characters->AddMovementInput(FVector::UpVector, MassageVal);
		}
	}
}

void UPersonControlsComponent::Turn(const FInputActionValue& InputActionValue)
{
	if(Characters!=nullptr)
	Characters->AddControllerYawInput(InputActionValue.Get<FInputActionValue::Axis1D>());
}

void UPersonControlsComponent::LookUp(const FInputActionValue& InputActionValue)
{
	if(Characters != nullptr)
	Characters->AddControllerPitchInput(InputActionValue.Get<FInputActionValue::Axis1D>());
}

void UPersonControlsComponent::StartTurbo(const FInputActionValue& InputActionValue)
{

}

void UPersonControlsComponent::StopTurbo(const FInputActionValue& InputActionValue)
{

}

void UPersonControlsComponent::Jump(const FInputActionValue& InputActionValue)
{
	if (Characters != nullptr)
		Characters->Jump();
}

void UPersonControlsComponent::Walk(const FInputActionValue& InputActionValue)
{
	if (gait != Gait::Walk)
		gait = Gait::Walk;
	else
		gait = Gait::Run;
}

void UPersonControlsComponent::StartSprint(const FInputActionValue& InputActionValue)
{
	gait = Gait::Sprint;
}

void UPersonControlsComponent::EndSprint(const FInputActionValue& InputActionValue)
{
	gait = Gait::Run;
}
