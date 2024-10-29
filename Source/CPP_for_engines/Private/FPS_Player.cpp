#include "FPS_Player.h"

#include "HealthComponent.h"
#include "WeaponBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


AFPS_Player::AFPS_Player()
{
	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(RootComponent);
	
	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	_WeaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Attach"));
	_WeaponAttachPoint->SetupAttachment(_Camera);

	_bIsSprinting = false;
	_WalkSpeedRatio = 0.5;
}

void AFPS_Player::Input_Look_Implementation(FVector2D Value)
{
	AddControllerPitchInput(-Value.Y);
	AddControllerYawInput(Value.X);
}

void AFPS_Player::Input_Move_Implementation(FVector2D Value)
{
	AddMovementInput(FVector::VectorPlaneProject(_Camera->GetForwardVector(), FVector::UpVector).GetSafeNormal(), (_bIsSprinting) ? Value.Y : Value.Y * _WalkSpeedRatio);
	AddMovementInput(_Camera->GetRightVector(), Value.X * _WalkSpeedRatio);
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
}

void AFPS_Player::Input_CrouchReleased_Implementation()
{
	ACharacter::UnCrouch();
}

void AFPS_Player::Input_SprintPressed_Implementation()
{
	_bIsSprinting = true;
}

void AFPS_Player::Input_SprintReleased_Implementation()
{
	_bIsSprinting = false;
}

void AFPS_Player::BeginPlay()
{
	Super::BeginPlay();
	
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
	UKismetSystemLibrary::LineTraceSingle()
}

UInputMappingContext* AFPS_Player::GetMappingContext_Implementation()
{
	return _InputMapping;
}

UBehaviorTree* AFPS_Player::GetBehaviorTree_Implementation()
{
	return _BeaviorTree;
}

void AFPS_Player::Handle_HealthDead(AController* Causer)
{
	//TODO:: implement
}

void AFPS_Player::Handle_HealthDamaged(float Ratio)
{
	//TODO:: use interface for binding
}
