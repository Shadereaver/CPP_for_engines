#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerDeathEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerDeathSignature, AController*, Causer);

UINTERFACE()
class UPlayerDeathEvent : public UInterface
{
	GENERATED_BODY()
};

class CPP_FOR_ENGINES_API IPlayerDeathEvent
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual FPlayerDeathSignature& GetPlayerDeathDelegate() = 0;
};
