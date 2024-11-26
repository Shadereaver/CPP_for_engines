#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponPickup.generated.h"

class UBoxComponent;
class AWeaponBase;

UCLASS()
class CPP_FOR_ENGINES_API AWeaponPickup : public AActor
{
	GENERATED_BODY()

public:
	AWeaponPickup();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> _Collider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeaponBase> _Weapon;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void Handle_Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
