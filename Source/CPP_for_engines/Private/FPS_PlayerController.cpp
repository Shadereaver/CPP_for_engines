#include "FPS_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Inputable.h"
#include "PawnOnDamageEvent.h"
#include "Widget_HUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


FPlayerDeathSignature& AFPS_PlayerController::GetPlayerDeathDelegate()
{
	return OnPlayerDeath;
}

void AFPS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIP = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EIP->BindAction(_LookAction, ETriggerEvent::Triggered, this, &AFPS_PlayerController::Look);
		EIP->BindAction(_MoveAction, ETriggerEvent::Triggered, this, &AFPS_PlayerController::Move);
		EIP->BindAction(_JumpAction, ETriggerEvent::Started, this, &AFPS_PlayerController::JumpPressed);
		EIP->BindAction(_JumpAction, ETriggerEvent::Completed, this, &AFPS_PlayerController::JumpReleased);
		EIP->BindAction(_AttackAction, ETriggerEvent::Started, this, &AFPS_PlayerController::AttackPressed);
		EIP->BindAction(_AttackAction, ETriggerEvent::Completed, this, &AFPS_PlayerController::AttackReleased);
		EIP->BindAction(_SprintAction, ETriggerEvent::Started, this, &AFPS_PlayerController::SprintPressed);
		EIP->BindAction(_SprintAction, ETriggerEvent::Completed, this, &AFPS_PlayerController::SprintReleased);
		EIP->BindAction(_CrouchAction, ETriggerEvent::Started, this, &AFPS_PlayerController::CrouchPressed);
		EIP->BindAction(_CrouchAction, ETriggerEvent::Completed, this, &AFPS_PlayerController::CrouchReleased);
		EIP->BindAction(_SpecialMovementAction, ETriggerEvent::Triggered, this, &AFPS_PlayerController::SpecialMovementPressed);
	}
}

void AFPS_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (_HUDWidgetClass)
	{
		_HUDWidget = CreateWidget<UWidget_HUD, AFPS_PlayerController*>(this, _HUDWidgetClass);
		_HUDWidget->AddToViewport();
		_HUDWidget->UpdateScore(0);
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


void AFPS_PlayerController::SprintPressed()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_SprintPressed(CurrentPawn);
		}
	}
}

void AFPS_PlayerController::SprintReleased()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_SprintReleased(CurrentPawn);
		}
	}
}

void AFPS_PlayerController::CrouchPressed()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_CrouchPressed(CurrentPawn);
		}
	}
}

void AFPS_PlayerController::CrouchReleased()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_CrouchReleased(CurrentPawn);
		}
	}
}

void AFPS_PlayerController::SpecialMovementPressed()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(CurrentPawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_SpacialMovementPressed(CurrentPawn);
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

	if (UKismetSystemLibrary::DoesImplementInterface(InPawn, UPawnOnDamageEvent::StaticClass()))
	{
		IPawnOnDamageEvent* IInPawn = Cast<IPawnOnDamageEvent>(InPawn);
		IInPawn->GetDamageDelegate().AddUniqueDynamic(this, &AFPS_PlayerController::Handle_OnDamage);
		IInPawn->RequestHealthUpdate();

		IInPawn->GetDeathDelegate().AddUniqueDynamic(this, &AFPS_PlayerController::Handle_OnDeath);
	}

	UGameplayStatics::GetPlayerCameraManager(this, 0)->ViewPitchMax = 90;
	UGameplayStatics::GetPlayerCameraManager(this, 0)->ViewPitchMin = -90;
}

void AFPS_PlayerController::OnUnPossess()
{
	if (UKismetSystemLibrary::DoesImplementInterface(GetPawn(), UPawnOnDamageEvent::StaticClass()))
	{
		IPawnOnDamageEvent* IPawn = Cast<IPawnOnDamageEvent>(GetPawn());
		IPawn->GetDamageDelegate().RemoveDynamic(this, &AFPS_PlayerController::Handle_OnDamage);
		IPawn->GetDeathDelegate().RemoveDynamic(this, &AFPS_PlayerController::Handle_OnDeath);
	}
	
	Super::OnUnPossess();
}

void AFPS_PlayerController::AddPoints_Implementation(int Points)
{
	_HUDWidget->UpdateScore(Points);
}

void AFPS_PlayerController::Handle_OnDamage(float Ratio)
{
	_HUDWidget->UpdateHealth(Ratio);
}

void AFPS_PlayerController::Handle_OnDeath(AController* Causer)
{
	OnPlayerDeath.Broadcast(Causer);
}



