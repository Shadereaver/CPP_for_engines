#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Weapon_Projectile.generated.h"

class AProjectile;

UCLASS(Abstract)
class CPP_FOR_ENGINES_API AWeapon_Projectile : public AWeaponBase
{
	GENERATED_BODY()

public:
	virtual void Fire() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProjectile> _ProjectileClass;
};
