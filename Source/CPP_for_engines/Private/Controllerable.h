#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Controllerable.generated.h"

UINTERFACE()
class UControllerable : public UInterface
{
	GENERATED_BODY()
};


class CPP_FOR_ENGINES_API IControllerable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddPoints(int Points);
};
