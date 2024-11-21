#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_RotateTowards.generated.h"

UCLASS()
class CPP_FOR_ENGINES_API UBTService_RotateTowards : public UBTService
{
	GENERATED_BODY()

	UBTService_RotateTowards();

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector Key_Key;
};
