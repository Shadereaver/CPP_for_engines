#include "FPS_Player.h"
#include "HealthComponent.h"
#include "Camera/CameraComponent.h"


AFPS_Player::AFPS_Player()
{
	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(RootComponent);

	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	
}

void AFPS_Player::Input_Look_Implementation(FVector2D Value)
{
	AddActorWorldRotation(FRotator(0.0f, Value.X, 0.0f));
	_Camera->AddLocalRotation(FRotator(Value.Y, 0.0f, 0.0f));
}

void AFPS_Player::Input_Move_Implementation(FVector2D Value)
{
	AddMovementInput(FVector::VectorPlaneProject(_Camera->GetForwardVector(), FVector::UpVector).GetSafeNormal(), Value.Y);
	AddMovementInput(_Camera->GetRightVector(), Value.X);
}

void AFPS_Player::Input_AttackPressed_Implementation()
{
	//TODO: make weapon attack
}

void AFPS_Player::Input_AttackReleased_Implementation()
{
	//TODO: make weapon stop
}

void AFPS_Player::Input_JumpPressed_Implementation()
{
	ACharacter::Jump();
}

void AFPS_Player::Input_JumpReleased_Implementation()
{
	ACharacter::StopJumping();
}

void AFPS_Player::Input_AimPressed_Implementation()
{
	//TODO:: make aim
}

void AFPS_Player::Input_AimReleased_Implementation()
{
	//TODO:: stop aim
}

void AFPS_Player::Input_Interact_Implementation()
{
	//TODO:: make interact
}

void AFPS_Player::Input_Reload_Implementation()
{
	//TODO:: make reload
}

UInputMappingContext* AFPS_Player::GetMappingContext_Implementation()
{
	return _InputMapping;
}



