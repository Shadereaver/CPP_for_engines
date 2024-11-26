#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class UArrowComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponFireSignature);

UCLASS(Abstract)
class CPP_FOR_ENGINES_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();

	UPROPERTY(BlueprintAssignable)
	FWeaponFireSignature OnFire;

	void StartFire();
	void StopFire();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _Root;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> _Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> _Muzzle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _FireDelay;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool _bOnCooldown;

	FTimerHandle _Cooldown;
	FTimerHandle _FireDelayTimer;

	UFUNCTION()
	virtual void Fire();

	UFUNCTION()
	void OffCooldown();
};
