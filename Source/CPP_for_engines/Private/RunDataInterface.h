#pragma once

#include "CoreMinimal.h"
#include "FRunData.h"
#include "UObject/Interface.h"
#include "RunDataInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameModeRunDataUpdateSignature, FPastRunData&, PastRunData);

UINTERFACE()
class URunDataInterface : public UInterface
{
	GENERATED_BODY()
};

class CPP_FOR_ENGINES_API IRunDataInterface
{
	GENERATED_BODY()

public:
	virtual FGameModeRunDataUpdateSignature& GetRunDataDelegate() = 0;
};
