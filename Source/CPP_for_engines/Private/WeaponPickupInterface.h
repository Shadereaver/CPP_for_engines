#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponPickupInterface.generated.h"

class AWeaponBase;

UINTERFACE()
class UWeaponPickupInterface : public UInterface
{
	GENERATED_BODY()
};

class CPP_FOR_ENGINES_API IWeaponPickupInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void ChangeWeapon(TSubclassOf<AWeaponBase> Weapon);
};
