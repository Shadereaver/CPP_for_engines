#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_InputFire.generated.h"

UCLASS()
class CPP_FOR_ENGINES_API UBTService_InputFire : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_InputFire();

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector Key_Pawn;
};
