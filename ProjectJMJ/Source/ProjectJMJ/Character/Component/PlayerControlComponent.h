// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "EnhancedInputComponent.h"
#include "InputTriggers.h"
#include "Misc/AssertionMacros.h"
#include "UObject/UObjectGlobals.h"
#include "GameFramework/Character.h"
#include "PlayerControlComponent.generated.h"
/**
 * 
 */
class AController;
class APawn;
class UEnhancedInputLocalPlayerSubsystem;
class UInputAction;
class UInputMappingContext;

UCLASS(Blueprintable, BlueprintType, Category = "Input", meta = (BlueprintSpawnableComponent))
class PROJECTJMJ_API UPlayerControlComponent : public UPawnComponent
{
	GENERATED_BODY()
public:
	virtual void OnRegister() override;
	virtual void OnUnregister() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PlayerControls")
	UInputMappingContext* InputMappingContext = nullptr;

	//�������ȼ�
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PlayerControls")
	int InputPriority = 0;

	UPROPERTY()
	ACharacter* Characters = nullptr;

	//��Input
	template<class UserClass, typename FuncType>
	bool BindInputAction(const UInputAction* Action, const ETriggerEvent EventType, UserClass* Object, FuncType Func)
	{

		if (ensure(InputComponent != nullptr) && ensure(Action != nullptr))
		{
			InputComponent->BindAction(Action, EventType, Object, Func);
			return true;
		}
		return false;
	}

	//��Input
	template<class UserClass, typename FuncType,typename VarTypes>
	bool BindInputAction(const UInputAction* Action, const ETriggerEvent EventType, UserClass* Object,FuncType Func,VarTypes Vars)
	{

		if (ensure(InputComponent != nullptr) && ensure(Action != nullptr))
		{
			InputComponent->BindAction(Action, EventType, Object, Func,Vars);
			return true;
		}
		return false;
	}
protected:

	//transient��ʾ�������ǡ���ʱ�ġ�����ʱ���Բ��ᱻ���л�
	UPROPERTY(transient)
	UEnhancedInputComponent* InputComponent;
	//�������ӳ��
	UFUNCTION(BlueprintNativeEvent,Category="PlayerControls")
	void AddPlayerControls(UEnhancedInputComponent* PlayerInputComponent);
	//�����Ƴ�ӳ��
	UFUNCTION(BlueprintNativeEvent,Category="PlayerControls")
	void RemovePlayerControls(UEnhancedInputComponent* PlayerInputComponent);

	//��ɫ�����Ƴ���
	UFUNCTION()
	virtual void OnPawnRestarted(APawn* Pawn);

	UFUNCTION()
	virtual void OnControllerChanged(APawn* Pawn,AController* OldController,AController* NewController);

	//����ӳ��
	virtual void SetupInputComponent(APawn* Pawn);
	//�ͷ�ӳ��
	virtual void ReleaseInputComponent(AController* OldController=nullptr);
	//�����ǿ������ϵͳ
	UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputSubsystem(AController* OldController=nullptr) const;

};
