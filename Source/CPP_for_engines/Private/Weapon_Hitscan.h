#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Weapon_Hitscan.generated.h"

UCLASS(Abstract)
class CPP_FOR_ENGINES_API AWeapon_Hitscan : public AWeaponBase
{
	GENERATED_BODY()

public:
	virtual void Fire() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _Damage;
};
