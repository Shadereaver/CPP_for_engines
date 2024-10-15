#include "Weapon_Projectile.h"

#include "Projectile.h"
#include "Components/ArrowComponent.h"

void AWeapon_Projectile::Fire()
{
	UWorld* const World = GetWorld();
	if (World == nullptr || _ProjectileClass == nullptr) {return;}

	FActorSpawnParameters SpawnParams;

	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	World->SpawnActor(_ProjectileClass, &_Muzzle->GetComponentTransform(), SpawnParams);
	
	Super::Fire();
}
