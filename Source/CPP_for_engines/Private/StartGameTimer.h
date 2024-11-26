#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StartGameTimer.generated.h"

UINTERFACE()
class UStartGameTimer : public UInterface
{
	GENERATED_BODY()
};

class CPP_FOR_ENGINES_API IStartGameTimer
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void StartTimer();
};
