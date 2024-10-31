#include "FPS_Player.h"

#include "HealthComponent.h"
#include "WeaponBase.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"


AFPS_Player::AFPS_Player()
{
	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(RootComponent);
	
	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	_WeaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Attach"));
	_WeaponAttachPoint->SetupAttachment(_Camera);

	_bIsSprinting = false;
	_WalkSpeedRatio = 0.5;

	_bIsMovingSpecial = false;
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
	if (_bIsMovingSpecial) {return;}
	_bIsMovingSpecial = true;

	FHitResult WallRightHitResult;
	FHitResult WallLeftHitResult;
	FHitResult RoofHitResult;
	FHitResult UpperFrontWallHitResult;
	FHitResult LowerFrontWallHitResult;
	
	UKismetSystemLibrary::LineTraceSingle(this,
		GetActorLocation(),
		GetActorLocation() + GetActorRightVector() * 100,
		UEngineTypes::ConvertToTraceType(ECC_WorldStatic),
		false,
		{},
		EDrawDebugTrace::ForDuration,
		WallRightHitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		5);

	UKismetSystemLibrary::LineTraceSingle(this,
		GetActorLocation(),
		GetActorLocation() + -GetActorRightVector() * 100,
		UEngineTypes::ConvertToTraceType(ECC_WorldStatic),
		false,
		{},
		EDrawDebugTrace::ForDuration,
		WallLeftHitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		5);

	UKismetSystemLibrary::LineTraceSingle(this,
		GetActorLocation(),
		GetActorLocation() + GetActorUpVector() * 200,
		UEngineTypes::ConvertToTraceType(ECC_WorldStatic),
		false,
		{},
		EDrawDebugTrace::ForDuration,
		RoofHitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		5);

	UKismetSystemLibrary::LineTraceSingle(this,
		GetActorLocation() + GetActorUpVector() * 100,
		(GetActorLocation() + GetActorUpVector() * 100) + GetActorForwardVector() * 100,
		UEngineTypes::ConvertToTraceType(ECC_WorldStatic),
		false,
		{},
		EDrawDebugTrace::ForDuration,
		UpperFrontWallHitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		5);

	UKismetSystemLibrary::LineTraceSingle(this,
		GetActorLocation() - GetActorUpVector() * 50,
		(GetActorLocation() - GetActorUpVector() * 50) + GetActorForwardVector() * 100,
		UEngineTypes::ConvertToTraceType(ECC_WorldStatic),
		false,
		{},
		EDrawDebugTrace::ForDuration,
		LowerFrontWallHitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		5);

	if (!RoofHitResult.bBlockingHit && !UpperFrontWallHitResult.bBlockingHit && LowerFrontWallHitResult.bBlockingHit)
	{
		AddActorLocalOffset(GetActorUpVector() * 200);
	}
	else if (_bIsSprinting && (WallLeftHitResult.bBlockingHit || WallRightHitResult.bBlockingHit))
	{
		UE_LOG(LogTemp, Display, TEXT("Dot: %f"), GetActorForwardVector().Dot(GetVelocity()));
	}

	_bIsMovingSpecial = false;
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
	OnDamaged.Broadcast(Ratio);
}

FPawnDamagedSignature& AFPS_Player::GetDamageDelegate()
{
	return OnDamaged;
}

FPawnDeathSignature& AFPS_Player::GetDeathDelegate()
{
	return OnDeath;
}

void AFPS_Player::RequestHealthUpdate()
{
	OnDamaged.Broadcast(_Health->Get_HealthRatio());
}
