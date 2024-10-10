#pragma once

#include "CoreMinimal.h"
#include "GameRule.h"
#include "GameRule_Target.generated.h"

class UTargetComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGRTargetRequestTargetsSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CPP_FOR_ENGINES_API UGameRule_Target : public UGameRule
{
	GENERATED_BODY()

public:
	UGameRule_Target();

	static inline FGRTargetRequestTargetsSignature OnRequestTargets;

	virtual void Init() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UTargetComponent>> _Targets;

	int _AmountRemaining;

private:
	UFUNCTION()
	void Handle_TargetRegistered(UTargetComponent* Target);
	UFUNCTION()
	void Handle_TargetDestroyed(UTargetComponent* Target, AController* Causer, int TargetValue);
};
