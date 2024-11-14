#include "TargetComponent.h"

#include "GameRule_Target.h"
#include "HealthComponent.h"


UTargetComponent::UTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	_PointsValue = 1;
}


void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	_Health = Owner->FindComponentByClass<UHealthComponent>();
	if (_Health == nullptr)
	{
		_Health = NewObject<UHealthComponent>(Owner, TEXT("Health"));

		Owner->AddInstanceComponent(_Health);

		_Health->RegisterComponent();

		Owner->Modify();
	}

	_Health->OnDead.AddUniqueDynamic(this, &UTargetComponent::Handle_HealthDead);

	UGameRule_Target::OnRequestTargets.AddUniqueDynamic(this, &UTargetComponent::Handle_GameRuleRequestTargets);
	
	OnTargetRegistered.Broadcast(this);
}

void UTargetComponent::Handle_HealthDead(AController* Causer)
{
	OnDestroyed.Broadcast(this, Causer, _PointsValue);
}

void UTargetComponent::Handle_GameRuleRequestTargets()
{
	OnTargetRegistered.Broadcast(this);
}

