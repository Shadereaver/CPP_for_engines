#pragma once

#include "CoreMinimal.h"
#include "Navigation/NavLinkProxy.h"
#include "WallRunNavLink.generated.h"

UCLASS()
class CPP_FOR_ENGINES_API AWallRunNavLink : public ANavLinkProxy
{
	GENERATED_BODY()

public:
	AWallRunNavLink();

protected:
	UFUNCTION()
	void Handle_OnLinkReached(AActor* MovingActor, const FVector& DestinationPoint);
};
