#include "WeaponBase.h"

#include "Components/ArrowComponent.h"


AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	_FireDelay = 1.f;

	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(RootComponent);

	_Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	_Muzzle->SetupAttachment(_Mesh);

	_bOnCooldown = false;
}

void AWeaponBase::StartFire()
{
	if (_bOnCooldown) {return;}
	_bOnCooldown = true;
	
	Fire();
	
	GetWorldTimerManager().SetTimer(_FireDelayTimer, this, &AWeaponBase::Fire, _FireDelay, true);
	GetWorldTimerManager().SetTimer(_Cooldown, this, &AWeaponBase::OffCooldown, _FireDelay);
}

void AWeaponBase::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(_FireDelayTimer);
}

void AWeaponBase::Fire()
{
	OnFire.Broadcast();
}

void AWeaponBase::OffCooldown()
{
	_bOnCooldown = false;
}

