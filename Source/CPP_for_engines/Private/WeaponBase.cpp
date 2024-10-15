#include "WeaponBase.h"

#include "Components/ArrowComponent.h"


AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	_FireDelay = 0.f;

	_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = _Root;

	_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	_Mesh->SetupAttachment(RootComponent);

	_Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	_Muzzle->SetupAttachment(_Mesh);
}

void AWeaponBase::StartFire()
{
	Fire();
	if (_FireDelay != 0.f)
	{
		GetWorld()->GetTimerManager().SetTimer(_FireDelayTimer, this, &AWeaponBase::Fire, _FireDelay);
	}
}

void AWeaponBase::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(_FireDelayTimer);
}

void AWeaponBase::Fire()
{
	OnFire.Broadcast();
}

