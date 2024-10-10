#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetComponent.generated.h"

class UHealthComponent;
class UTargetComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTargetDestroyedSignature, UTargetComponent*, Target, AController*, Destroyer, int, TargetValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetRegisteredSigniture, UTargetComponent*, Target);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CPP_FOR_ENGINES_API UTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTargetComponent();

	UPROPERTY(BlueprintAssignable)
	FTargetDestroyedSignature OnDestroyed;

	static inline FTargetRegisteredSigniture OnTargetRegistered;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=0))
	int _PointsValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UHealthComponent> _Health;
	
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void Handle_HealthDead(AController* Causer);
	UFUNCTION()
	void Handle_GameRuleRequestTargets();
};
