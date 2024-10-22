#include "HealthComponent.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	_MaxHealth = 100.f;
	_CurrentHealth = _MaxHealth;
}

float UHealthComponent::Get_HealthRatio()
{
	return _CurrentHealth/_MaxHealth;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddUniqueDynamic(this, &UHealthComponent::DamageTaken);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	const float change = FMath::Min(_CurrentHealth, Damage);
	_CurrentHealth -= change;
	OnDamaged.Broadcast(_CurrentHealth/ _MaxHealth);
	if(FMath::IsNearlyZero(_CurrentHealth)) {OnDead.Broadcast(InstigatedBy);}
}
