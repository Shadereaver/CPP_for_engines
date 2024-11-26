#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UNavModifierComponent;
class UBoxComponent;

UCLASS()
class CPP_FOR_ENGINES_API ADoor : public AActor
{
	GENERATED_BODY()

public:
	ADoor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> _Collider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UNavModifierComponent> _NavModifier;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool _bHasStarted;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void Handle_Overlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
