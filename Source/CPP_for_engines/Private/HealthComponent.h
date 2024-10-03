#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CPP_FOR_ENGINES_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float _CurrentHealth;
	
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
