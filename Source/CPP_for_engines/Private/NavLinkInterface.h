#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NavLinkInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNavLinkInterfaceResumePathSignature, AActor*, Agent);

UINTERFACE()
class UNavLinkInterface : public UInterface
{
	GENERATED_BODY()
};


class CPP_FOR_ENGINES_API INavLinkInterface
{
	GENERATED_BODY()

public:
	virtual FNavLinkInterfaceResumePathSignature& GetResumeDelegate() = 0;
	virtual void StartWallRun(const FVector& DestinationPoint) = 0;
};
