#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnOnDamageEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPawnDamagedSignature, float, Ratio);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPawnDeathSignature);

UINTERFACE()
class UPawnOnDamageEvent : public UInterface
{
	GENERATED_BODY()
};

class CPP_FOR_ENGINES_API IPawnOnDamageEvent
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual FPawnDamagedSignature& GetDamageDelegate() = 0;
	UFUNCTION()
	virtual FPawnDeathSignature& GetDeathDelegate() = 0;

	UFUNCTION()
	virtual void RequestHealthUpdate() = 0;
};
