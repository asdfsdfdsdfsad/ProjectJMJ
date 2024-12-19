#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Input/PersonControlsComponent.h"
#include "ChooserFunctionLibrary.h"
#include "PoseSearch/PoseSearchLibrary.h"
#include "MotionWarpingComponent.h"
#include "ProjectJMJ/AbilitySystem/PersonAbilitySystemComponent.h"
#include "Person.generated.h"

class UPersonControlsComponent;
class UMotionWarpingComponent;
class UPersonAbilitySystemComponent;
class UChooserTable;
class UNormalAttackAbility;
class UAttributeComponent;

UCLASS()
class PROJECTJMJ_API APerson : public ACharacter
{
	GENERATED_BODY()

public:
	// 设置此 character 属性的默认值
	APerson();

protected:
	// 已在游戏开始或生成时调用
	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateMovement();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Speed")
	float Speed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Jump")
	float Height;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Jump")
	float Width;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Curve")
	TObjectPtr<UCurveFloat> Curve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chooser")
	TObjectPtr<UChooserTable> ChooserTable;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Speed")
	FVector WalkSpeeds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	FVector RunSpeeds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	FVector SprintSpeeds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	FVector CrouchSpeeds;

public:
	virtual void Jump() override;

	// 已调用每个帧
	virtual void Tick(float DeltaTime) override;

	// 调用以绑定要输出的功能
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gait")
	Gait EGait;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UPersonControlsComponent> PersonControlsComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UPersonAbilitySystemComponent> PersonAbilitySystemComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeComponent> AttributeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TSubclassOf<UNormalAttackAbility> AttackAbility;
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;
	UFUNCTION()
	void MontageEnd(UAnimMontage* Montage, bool bInterrupted);
};
