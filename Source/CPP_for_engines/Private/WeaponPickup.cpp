#include "WeaponPickup.h"

#include "WeaponPickupInterface.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"


AWeaponPickup::AWeaponPickup()
{
	PrimaryActorTick.bCanEverTick = false;

	_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("_Collider"));
	RootComponent = _Collider;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("_Mesh"));
	_Mesh->SetupAttachment(RootComponent);
}

void AWeaponPickup::BeginPlay()
{
	Super::BeginPlay();

	_Collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &AWeaponPickup::Handle_Overlap);
}

void AWeaponPickup::Handle_Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UWeaponPickupInterface::StaticClass()))
	{
		IWeaponPickupInterface::Execute_ChangeWeapon(OtherActor, _Weapon);
	}
}
