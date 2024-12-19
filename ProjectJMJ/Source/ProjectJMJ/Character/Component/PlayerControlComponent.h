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

	//输入优先级
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PlayerControls")
	int InputPriority = 0;

	UPROPERTY()
	ACharacter* Characters = nullptr;

	//绑定Input
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

	//绑定Input
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

	//transient表示该属性是“临时的”。临时属性不会被序列化
	UPROPERTY(transient)
	UEnhancedInputComponent* InputComponent;
	//重载添加映射
	UFUNCTION(BlueprintNativeEvent,Category="PlayerControls")
	void AddPlayerControls(UEnhancedInputComponent* PlayerInputComponent);
	//重载移除映射
	UFUNCTION(BlueprintNativeEvent,Category="PlayerControls")
	void RemovePlayerControls(UEnhancedInputComponent* PlayerInputComponent);

	//角色重生移除绑定
	UFUNCTION()
	virtual void OnPawnRestarted(APawn* Pawn);

	UFUNCTION()
	virtual void OnControllerChanged(APawn* Pawn,AController* OldController,AController* NewController);

	//设置映射
	virtual void SetupInputComponent(APawn* Pawn);
	//释放映射
	virtual void ReleaseInputComponent(AController* OldController=nullptr);
	//获得增强输入子系统
	UEnhancedInputLocalPlayerSubsystem* GetEnhancedInputSubsystem(AController* OldController=nullptr) const;

};
