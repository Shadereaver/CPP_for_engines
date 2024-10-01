#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirstActor.generated.h"

class URotatingMovementComponent;
class UArrowComponent;

UCLASS(Abstract)
class CPP_FOR_ENGINES_API AFirstActor : public AActor
{
	GENERATED_BODY()

public:
	AFirstActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite);
	TObjectPtr<USceneComponent> _Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite);
	TObjectPtr<UStaticMeshComponent> _Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite);
	TObjectPtr<UArrowComponent> _Arrow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<URotatingMovementComponent> _Rotate;
};
