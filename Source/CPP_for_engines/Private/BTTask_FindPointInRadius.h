#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindPointInRadius.generated.h"

UCLASS()
class CPP_FOR_ENGINES_API UBTTask_FindPointInRadius : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FindPointInRadius();

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector Key_TargetPos;
};
