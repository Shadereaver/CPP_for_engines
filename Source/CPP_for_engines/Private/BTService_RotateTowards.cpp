#include "BTService_RotateTowards.h"

#include "AIController.h"

UBTService_RotateTowards::UBTService_RotateTowards()
{
	bNotifyTick = true;
	bNotifyBecomeRelevant = false;
	bNotifyCeaseRelevant = false;
}

void UBTService_RotateTowards::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();

	if (ensure(BBAsset))
	{
		Key_Key.ResolveSelectedKey(*BBAsset);
	}
}

void UBTService_RotateTowards::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const FVector PawnLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
	
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
