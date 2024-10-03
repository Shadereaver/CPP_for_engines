#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirstActor.generated.h"

class UBoxComponent;
class UArrowComponent;

UCLASS(Abstract)
class CPP_FOR_ENGINES_API AFirstActor : public AActor
{
	GENERATED_BODY()

public:
	AFirstActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite);
	TObjectPtr<UBoxComponent> _Box;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite);
	TObjectPtr<UStaticMeshComponent> _Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite);
	TObjectPtr<UArrowComponent> _Arrow;

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void Handle_ColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
