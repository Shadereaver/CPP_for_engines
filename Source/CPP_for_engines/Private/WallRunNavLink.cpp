#include "WallRunNavLink.h"

#include "NavLinkInterface.h"
#include "Kismet/KismetSystemLibrary.h"


AWallRunNavLink::AWallRunNavLink()
{
	PrimaryActorTick.bCanEverTick = false;

	OnSmartLinkReached.AddUniqueDynamic(this, &AWallRunNavLink::Handle_OnLinkReached);
}

void AWallRunNavLink::Handle_OnLinkReached(AActor* MovingActor, const FVector& DestinationPoint)
{
	if (UKismetSystemLibrary::DoesImplementInterface(MovingActor, UNavLinkInterface::StaticClass()))
	{
		INavLinkInterface* IMovingActor = Cast<INavLinkInterface>(MovingActor);

		IMovingActor->GetResumeDelegate().AddUniqueDynamic(this, &AWallRunNavLink::ResumePathFollowing);
		
		IMovingActor->StartWallRun(DestinationPoint);
	}
}

