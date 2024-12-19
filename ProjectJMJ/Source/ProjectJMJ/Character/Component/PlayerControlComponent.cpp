// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControlComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void UPlayerControlComponent::OnRegister()
{
	Super::OnRegister();

	UWorld* world = GetWorld();
	APawn* MyOwner = GetPawn<APawn>();

	if (ensure(MyOwner) && world->IsGameWorld())
	{
		MyOwner->ReceiveRestartedDelegate.AddDynamic(this, &UPlayerControlComponent::OnPawnRestarted);
		MyOwner->ReceiveControllerChangedDelegate.AddDynamic(this, &UPlayerControlComponent::OnControllerChanged);
	}

	if (MyOwner->InputComponent) {
	
		OnPawnRestarted(MyOwner);
	}

	ACharacter* Character = GetPawnChecked<ACharacter>();
	if (Character != nullptr)
		Characters = Character;

}

void UPlayerControlComponent::OnUnregister() {

	UWorld* world = GetWorld();
	if (world && world->IsGameWorld())
	{
		ReleaseInputComponent();
		APawn* MyOwner = GetPawn<APawn>();
		if (MyOwner) {
	
			MyOwner->ReceiveRestartedDelegate.RemoveAll(this);
			MyOwner->ReceiveControllerChangedDelegate.RemoveAll(this);
		}
	}
	Super::OnUnregister();
}

void UPlayerControlComponent::OnPawnRestarted(APawn* Pawn)
{
	if (ensure(Pawn && Pawn == GetOwner()) && Pawn->InputComponent) {
		ReleaseInputComponent();
		if (Pawn->InputComponent) {
		
			SetupInputComponent(Pawn);
		
		}
	}
}

void UPlayerControlComponent::OnControllerChanged(APawn* Pawn,AController* OldController,AController* NewController) {
	if (ensure(Pawn && Pawn == GetOwner()) && OldController) 
	{
		ReleaseInputComponent(OldController);
	}

}

void UPlayerControlComponent::SetupInputComponent(APawn* Pawn) {
	InputComponent = CastChecked<UEnhancedInputComponent>(Pawn->InputComponent);

	if (ensureMsgf(InputComponent, TEXT("¿ØÖÆÊäÈëÉèÖÃÊ§°Ü£¡")))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputSubsystem();
		check(Subsystem);
		if (InputMappingContext)
		{
			Subsystem->AddMappingContext(InputMappingContext,InputPriority);
		}
		AddPlayerControls(InputComponent);
	}
}

void UPlayerControlComponent::ReleaseInputComponent(AController* OldController) {
	UEnhancedInputLocalPlayerSubsystem* Subsystem = GetEnhancedInputSubsystem(OldController);
	if (Subsystem && InputComponent) {
		RemovePlayerControls(InputComponent);
		if (InputMappingContext) {
			Subsystem->RemoveMappingContext(InputMappingContext);
		}
	}
	InputComponent = nullptr;
}

void UPlayerControlComponent::AddPlayerControls_Implementation(UEnhancedInputComponent* PlayerInputComponent)
{

}

void UPlayerControlComponent::RemovePlayerControls_Implementation(UEnhancedInputComponent* PlayerInputComponent)
{

}

UEnhancedInputLocalPlayerSubsystem* UPlayerControlComponent::GetEnhancedInputSubsystem(AController* OldController) const {
	const APlayerController* PC = GetController<APlayerController>();
	if (!PC) {
	
		PC = Cast<APlayerController>(OldController);
		if (!PC) {
			return nullptr;
		}
	}

	const ULocalPlayer* LP = PC->GetLocalPlayer();
	if (!LP) {
		return nullptr;
	}
	return LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
}


