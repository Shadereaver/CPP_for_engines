#include "FPS_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Inputable.h"
#include "Kismet/KismetSystemLibrary.h"


void AFPS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIP = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EIP->BindAction(_LookAction, ETriggerEvent::Triggered, this, &AFPS_PlayerController::Look);
		EIP->BindAction(_MoveAction, ETriggerEvent::Triggered, this, &AFPS_PlayerController::Move);
		EIP->BindAction(_JumpAction, ETriggerEvent::Triggered, this, &AFPS_PlayerController::JumpPressed);
		EIP->BindAction(_JumpAction, ETriggerEvent::Completed, this, &AFPS_PlayerController::JumpReleased);
		EIP->BindAction(_AttackAction, ETriggerEvent::Started, this, &AFPS_PlayerController::AttackPressed);
		EIP->BindAction(_AttackAction, ETriggerEvent::Completed, this, &AFPS_PlayerController::AttackReleased);
	}
}

void AFPS_PlayerController::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_Look(CurrentPawn, LookVector);
		}
	}
}

void AFPS_PlayerController::Move(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();

	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_Move(CurrentPawn, MoveVector);
		}
	}
}

void AFPS_PlayerController::JumpPressed()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_JumpPressed(CurrentPawn);
		}
	}
}

void AFPS_PlayerController::JumpReleased()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_JumpReleased(CurrentPawn);
		}
	}
}

void AFPS_PlayerController::AttackPressed()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_AttackPressed(CurrentPawn);
		}
	}
}

void AFPS_PlayerController::AttackReleased()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_AttackReleased(CurrentPawn);
		}
	}
}

void AFPS_PlayerController::AimPressed()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_AimPressed(CurrentPawn);
		}
	}
}

void AFPS_PlayerController::AimReleased()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_AimReleased(CurrentPawn);
		}
	}
}

void AFPS_PlayerController::InteractPressed()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_Interact(CurrentPawn);
		}
	}
}

void AFPS_PlayerController::ReloadPressed()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_Reload(CurrentPawn);
		}
	}
}

void AFPS_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (UKismetSystemLibrary::DoesImplementInterface(InPawn, UInputable::StaticClass()))
		{
			Subsystem->AddMappingContext(IInputable::Execute_GetMappingContext(InPawn), 0);
		}
	}
}
