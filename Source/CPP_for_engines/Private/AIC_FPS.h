#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Perception/AIPerceptionTypes.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "AIC_FPS.generated.h"

class UAISenseConfig_Sight;

UCLASS()
class CPP_FOR_ENGINES_API AAIC_FPS : public AAIController
{
	GENERATED_BODY()

public:
	AAIC_FPS();

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAIPerceptionComponent> _AIPerception;
	TObjectPtr<UAISenseConfig_Sight> _AISense_Sight;

	UPROPERTY(EditDefaultsOnly)
	FName _Key_TargetActor;

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UFUNCTION()
	void Handle_TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
