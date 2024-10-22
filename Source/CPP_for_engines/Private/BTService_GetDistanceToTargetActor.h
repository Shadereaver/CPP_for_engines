#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_GetDistanceToTargetActor.generated.h"

UCLASS()
class CPP_FOR_ENGINES_API UBTService_GetDistanceToTargetActor : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_GetDistanceToTargetActor();

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector Key_pawn;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector Key_TargetActor;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector Key_Distance;
};
