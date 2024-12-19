#include "Person.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/KismetMathLibrary.h>
#include "PoseSearch/PoseSearchResult.h"
#include "ProjectJMJ/AbilitySystem/AbilityFeature/NormalAttackAbility.h"
#include "KismetAnimationLibrary.h"
#include "ProjectJMJ/Character/Component/AttributeComponent.h"


// 设置默认值
APerson::APerson()
{
	PersonControlsComponent = CreateDefaultSubobject<UPersonControlsComponent>(TEXT("PersonControls"));
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping"));
	PersonAbilitySystemComponent= CreateDefaultSubobject<UPersonAbilitySystemComponent>(TEXT("AbilitySystem"));
	AttributeComponent= CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComp"));
	// 设置此 character，以调用每个帧的 Tick()。如果不需要，可以禁用此功能以提高性能。
	PrimaryActorTick.bCanEverTick = true;
}

// 已在游戏开始或生成时调用
void APerson::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this,&ThisClass::MontageEnd);
}

// 已调用每个帧
void APerson::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMovement();
}

// 调用以绑定要输出的功能
void APerson::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APerson::MontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void APerson::UpdateMovement()
{
	//GetComponents
	Speed = GetCharacterMovement()->Velocity.Length();
	float StrafsSpeedMap=UKismetAnimationLibrary::CalculateDirection(GetCharacterMovement()->Velocity, GetActorRotation());
	StrafsSpeedMap=FMath::Abs(StrafsSpeedMap);
	if (Curve == nullptr)return;
	StrafsSpeedMap=Curve->GetFloatValue(StrafsSpeedMap);
	FVector SpeedVector;
	if (GetCharacterMovement()->IsCrouching()) {
		SpeedVector = CrouchSpeeds;
	}
	else 
	{
		switch (PersonControlsComponent->gait) {
		case Gait::Walk:
			SpeedVector = WalkSpeeds;
			break;
		case Gait::Run:
			SpeedVector = RunSpeeds;
			break;
		case Gait::Sprint:
			SpeedVector = SprintSpeeds;
			break;
		}
	}
	EGait = PersonControlsComponent->gait;
	float MaxSpeed;
	if (StrafsSpeedMap<1)
	{
		MaxSpeed = UKismetMathLibrary::MapRangeClamped(StrafsSpeedMap, 0.0f, 1.0f, SpeedVector.X, SpeedVector.Y);
	}
	else 
	{
		MaxSpeed = UKismetMathLibrary::MapRangeClamped(StrafsSpeedMap, 1.0f, 2.0f, SpeedVector.Y, SpeedVector.Z);
	}
	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;
	GetCharacterMovement()->MaxWalkSpeedCrouched = MaxSpeed;
}

void APerson::Jump()
{
	Super::Jump();
	FVector StartLocation = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	float Distance=UKismetMathLibrary::MapRangeClamped(Speed,0.0f,500.0f,100.0f,400.0f);
	FVector EndLocation = StartLocation + (ForwardVector*Distance);
	TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;
	
	UKismetSystemLibrary::LineTraceSingleByProfile(this, StartLocation, EndLocation,NAME_None,false, ActorsToIgnore,EDrawDebugTrace::ForDuration,HitResult,true,FLinearColor::Red,FLinearColor::Green,2);
	if (HitResult.bBlockingHit)
	{
		StartLocation = HitResult.ImpactPoint+FVector(0.0f,0.0f,200.0f);
		EndLocation = HitResult.ImpactPoint;
		UKismetSystemLibrary::CapsuleTraceSingle(GetWorld(),StartLocation,EndLocation,30.0f,0.0f,ETraceTypeQuery::TraceTypeQuery1,false,ActorsToIgnore,EDrawDebugTrace::ForDuration,HitResult,true, FLinearColor::Red, FLinearColor::Green, 2);
		if (HitResult.bBlockingHit) {
			StartLocation = HitResult.ImpactPoint;
			Height = StartLocation.Z;
			UKismetSystemLibrary::CapsuleTraceSingle(GetWorld(), StartLocation + (ForwardVector * 100), HitResult.ImpactPoint, 30.0f, 0.0f, ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Red, FLinearColor::Green, 2);
			if (HitResult.bBlockingHit) {
				EndLocation = HitResult.ImpactPoint;
				Width = FVector::Distance(EndLocation, StartLocation);
				if (ChooserTable == nullptr)return;
				TArray<UObject*> AssetsToSearch = UChooserFunctionLibrary::EvaluateChooserMulti(this, ChooserTable,UAnimMontage::StaticClass());
				FPoseSearchBlueprintResult Result;
				FPoseSearchFutureProperties Future;
				UPoseSearchLibrary::MotionMatch(GetMesh()->GetAnimInstance(), AssetsToSearch, FName("PoseHistory"), Future, Result, 4532);
				MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation(FName("FrontLedge"), StartLocation, GetActorRotation());
				
				MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation(FName("EndLedge"),FVector(GetActorLocation().X, GetActorLocation().Y,0.0f), GetActorRotation());
				
				MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation(FName("BackLedge"), StartLocation, GetActorRotation());  

				if (Result.SelectedAnimation == nullptr)return;
				const UAnimMontage* AnimMontage =Cast<UAnimMontage>(Result.SelectedAnimation);
				UAnimMontage* AnimMontage2 =const_cast<UAnimMontage*>(AnimMontage);
				if (AnimMontage2 == nullptr)return;
				GetMesh()->GetAnimInstance()->Montage_Play(AnimMontage2, Result.WantedPlayRate, EMontagePlayReturnType::MontageLength, Result.SelectedTime);
				GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
			}
		}
	}

}
