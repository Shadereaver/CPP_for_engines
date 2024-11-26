#include "FPS_Player.h"

#include "HealthComponent.h"
#include "WeaponBase.h"
#include "Widget_EnemyHealthBar.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AFPS_Player::AFPS_Player()
{
	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(RootComponent);
	
	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	_WeaponAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Attach"));
	_WeaponAttachPoint->SetupAttachment(_Camera);

	_HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("_HealthBar"));
	_HealthBar->SetupAttachment(RootComponent);

	_bIsSprinting = false;
	_WalkSpeedRatio = 0.5;

	_bIsMovingSpecial = false;
	_bIsRightWallRun = false;
	_bHasWallJumped = false;

	_TeamId = FGenericTeamId(2);
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

	if (_bIsWallRunning && !_bHasWallJumped)
	{
		if (_bIsRightWallRun)
		{
			GetCharacterMovement()->AddImpulse((_Camera->GetForwardVector() + -_Camera->GetRightVector()) * 750, true);
		}
		else
		{
			GetCharacterMovement()->AddImpulse((_Camera->GetForwardVector() + _Camera->GetRightVector()) * 750, true);
		}
		_bHasWallJumped = true;
	}
}

void AFPS_Player::Input_JumpReleased_Implementation()
{
	ACharacter::StopJumping();
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

	_HealthBarRef = Cast<UWidget_EnemyHealthBar>(_HealthBar->GetWidget());
	if (_HealthBarRef)
	{
		_HealthBarRef->UpdateHealth(_Health->Get_HealthRatio());
	}
	
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


	FHitResult RoofHitResult;
	FHitResult UpperFrontWallHitResult;
	FHitResult LowerFrontWallHitResult;

	UKismetSystemLibrary::LineTraceSingle(this,
		GetActorLocation(),
		GetActorLocation() + GetActorUpVector() * 200,
		UEngineTypes::ConvertToTraceType(ECC_WorldStatic),
		false,
		{},
		EDrawDebugTrace::None,
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
		EDrawDebugTrace::None,
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
		EDrawDebugTrace::None,
		LowerFrontWallHitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		5);

	if (!RoofHitResult.bBlockingHit && !UpperFrontWallHitResult.bBlockingHit && LowerFrontWallHitResult.bBlockingHit)
	{
		GetCharacterMovement()->AddImpulse(GetActorUpVector() * 600, true);
		_bIsMovingSpecial = false;
	}
	else
	{
		WallRun();
	}
}

UInputMappingContext* AFPS_Player::GetMappingContext_Implementation()
{
	return _InputMapping;
}

UBehaviorTree* AFPS_Player::GetBehaviorTree_Implementation()
{
	return _BehaviorTree;
}

FNavLinkInterfaceResumePathSignature& AFPS_Player::GetResumeDelegate()
{
	return OnResume;
}

void AFPS_Player::StartWallRun(const FVector& DestinationPoint)
{
	AIWallRun(DestinationPoint);

	GetWorldTimerManager().SetTimer(_TimerAIWallRunLimit, this, &AFPS_Player::ResumeNav, 5.f);
}

FGenericTeamId AFPS_Player::GetGenericTeamId() const
{
	return _TeamId;
}

void AFPS_Player::ChangeWeapon_Implementation(TSubclassOf<AWeaponBase> Weapon)
{
	_WeaponRef->Destroy();
	_DefaultWeapon = Weapon;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;
	_WeaponRef = GetWorld()->SpawnActor<AWeaponBase>(_DefaultWeapon, _WeaponAttachPoint->GetComponentTransform(), SpawnParams);
	_WeaponRef->AttachToComponent(_WeaponAttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void AFPS_Player::Handle_HealthDead(AController* Causer)
{
	OnDeath.Broadcast(Causer);
	_WeaponRef->Destroy();
	GetWorldTimerManager().SetTimer(_DeathTimer, this, &AFPS_Player::Death, 0.5);
}

void AFPS_Player::Handle_HealthDamaged(float Ratio)
{
	_HealthBarRef->UpdateHealth(Ratio);
	OnDamaged.Broadcast(Ratio);
}

void AFPS_Player::Landed(const FHitResult& Hit)
{
	GetWorldTimerManager().ClearTimer(_TimerWallRunUpdate);

	WallrunReset();

	_bHasWallJumped = false;
}

void AFPS_Player::WallRun()
{
	FHitResult WallRightHitResult;
	FHitResult WallRightBackHitResult;
	FHitResult WallLeftHitResult;
	FHitResult WallLeftBackHitResult;
	
	UKismetSystemLibrary::LineTraceSingle(this,
		GetActorLocation(),
		GetActorLocation() + GetActorRightVector() * 100,
		UEngineTypes::ConvertToTraceType(ECC_WorldStatic),
		false,
		{},
		EDrawDebugTrace::None,
		WallRightHitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		5);

	UKismetSystemLibrary::LineTraceSingle(this,
		GetActorLocation(),
		GetActorLocation()  + (GetActorRightVector() + FVector(1,0,0)) * 100,
		UEngineTypes::ConvertToTraceType(ECC_WorldStatic),
		false,
		{},
		EDrawDebugTrace::None,
		WallRightBackHitResult,
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
		EDrawDebugTrace::None,
		WallLeftHitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		5);

	UKismetSystemLibrary::LineTraceSingle(this,
		GetActorLocation(),
		GetActorLocation() + (-GetActorRightVector() + FVector(1,0,0)) * 100,
		UEngineTypes::ConvertToTraceType(ECC_WorldStatic),
		false,
		{},
		EDrawDebugTrace::None,
		WallLeftBackHitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		5);

	bool bDoesTraceHit = WallLeftHitResult.bBlockingHit || WallRightHitResult.bBlockingHit ||
		WallLeftBackHitResult.bBlockingHit || WallRightBackHitResult.bBlockingHit;

	bool bIsMovingForwards = GetActorForwardVector().Dot(GetVelocity()) > GetCharacterMovement()->MaxWalkSpeed * 0.5;
	
	if (_bIsSprinting && bDoesTraceHit && bIsMovingForwards)
	{
		GetCharacterMovement()->GravityScale = 0.5f;
		_bIsWallRunning = true;
		_bIsRightWallRun = (WallRightHitResult.bBlockingHit || WallRightBackHitResult.bBlockingHit) ? true : false;
	}
	else
	{
		WallrunReset();
	}
}

void AFPS_Player::AIWallRun(FVector Dest)
{
	if (!GetActorLocation().Equals(Dest))
	{
		_bIsWallRunning = true;
		_bIsMovingSpecial = true;
		
		GetCharacterMovement()->GravityScale = 0.f;
		GetCharacterMovement()->AddImpulse((Dest - GetActorLocation()) * 10);

		FTimerDelegate Timerdel;
		Timerdel.BindUFunction(this, FName("AIWallRun"), Dest);
		GetWorldTimerManager().SetTimer(_TimerAIWallRunUpdate, Timerdel, 0.01f, true);
	}
	else
	{
		ResumeNav();
	}
}

void AFPS_Player::WallrunReset()
{
	GetCharacterMovement()->GravityScale = 1;
		
	_bIsWallRunning = false;
	_bIsMovingSpecial = false;
}

void AFPS_Player::ResumeNav()
{
	OnResume.Broadcast(this);
	OnResume.Clear();

	GetWorldTimerManager().ClearTimer(_TimerAIWallRunUpdate);

	WallrunReset();
}

void AFPS_Player::Death()
{
	Destroy();
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
