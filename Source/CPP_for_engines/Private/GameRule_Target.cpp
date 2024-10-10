#include "GameRule_Target.h"

#include "TargetComponent.h"


UGameRule_Target::UGameRule_Target()
{
	PrimaryComponentTick.bCanEverTick = false;

	_AmountRemaining = 0;
}

void UGameRule_Target::Init()
{
	Super::Init();

	UTargetComponent::OnTargetRegistered.AddUniqueDynamic(this, &UGameRule_Target::Handle_TargetRegistered);
	OnRequestTargets.Broadcast();
}

void UGameRule_Target::Handle_TargetRegistered(UTargetComponent* Target)
{
	if (_Targets.Contains(Target)) {return;}

	_Targets.Add(Target);

	Target->OnDestroyed.AddUniqueDynamic(this, &UGameRule_Target::Handle_TargetDestroyed);

	_AmountRemaining++;
}

void UGameRule_Target::Handle_TargetDestroyed(UTargetComponent* Target, AController* Causer, int TargetValue)
{
	_Targets.Remove(Target);
	_AmountRemaining--;

	BroadcastPointsScored(Causer, TargetValue);

	if (_AmountRemaining == 0)
	{
		BroadcastComplete();
	}
}



