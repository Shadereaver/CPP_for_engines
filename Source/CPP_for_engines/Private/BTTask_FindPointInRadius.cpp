#include "BTTask_FindPointInRadius.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPointInRadius::UBTTask_FindPointInRadius()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;
}

void UBTTask_FindPointInRadius::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();

	if (ensure(BBAsset))
	{
		Key_TargetPos.ResolveSelectedKey(*BBAsset);
	}
}

EBTNodeResult::Type UBTTask_FindPointInRadius::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FVector Origin = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
	FVector Point;
	
	if (UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, Origin, Point, 1000))
	{
		UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();

		BBComp->SetValueAsVector(Key_TargetPos.SelectedKeyName, Point);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Aborted;
}
