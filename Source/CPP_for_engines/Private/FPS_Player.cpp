#include "FPS_Player.h"
#include "HealthComponent.h"
#include "WeaponBase.h"
#include "Camera/CameraComponent.h"


AFPS_Player::AFPS_Player()
{
	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(RootComponent);

	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	_WeaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Attach"));
	_WeaponAttachPoint->SetupAttachment(_Camera);
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
	if (_WeaponRef)
	{
		_WeaponRef->StartFire();
	}
}

void AFPS_Player::Input_AttackReleased_Implementation()
{
	if (_WeaponRef)
	{
		_WeaponRef->StopFire();
	}
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

void AFPS_Player::Input_CrouchPressed_Implementation()
{
	ACharacter::Crouch();
	_Camera->SetRelativeLocation({0.0f, 0.0f, CrouchedEyeHeight});
}

void AFPS_Player::Input_CrouchReleased_Implementation()
{
	ACharacter::UnCrouch();
	_Camera->SetRelativeLocation({0.0f, 0.0f, BaseEyeHeight});
}

void AFPS_Player::Input_SprintPressed_Implementation()
{
	//TODO:: Start sprint
}

void AFPS_Player::Input_SprintReleased_Implementation()
{
	//TODO:: Stop sprint
}

void AFPS_Player::BeginPlay()
{
	Super::BeginPlay();
	
	_Camera->SetRelativeLocation({0.0f, 0.0f, BaseEyeHeight});

	_Health->OnDead.AddUniqueDynamic(this, &AFPS_Player::Handle_HealthDead);
	_Health->OnDamaged.AddUniqueDynamic(this, &AFPS_Player::Handle_HealthDamaged);

	if (_DefaultWeapon)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = this;
		_WeaponRef = GetWorld()->SpawnActor<AWeaponBase>(_DefaultWeapon, _WeaponAttachPoint->GetComponentTransform(), SpawnParams);
		_WeaponRef->AttachToComponent(_WeaponAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}

void AFPS_Player::Input_SpacialMovementPressed_Implementation()
{
	//TODO:: Make special movement abilities.
}

UInputMappingContext* AFPS_Player::GetMappingContext_Implementation()
{
	return _InputMapping;
}

void AFPS_Player::Handle_HealthDead(AController* Causer)
{
	//TODO:: implement
}

void AFPS_Player::Handle_HealthDamaged(float Current, float Max, float Change)
{
	//TODO:: implement
}



