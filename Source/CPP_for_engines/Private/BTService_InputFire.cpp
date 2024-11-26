#include "BTService_InputFire.h"

#include "Inputable.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UBTService_InputFire::UBTService_InputFire()
{
	bNotifyTick = true;
	bNotifyBecomeRelevant = false;
	bNotifyCeaseRelevant = false;

	Key_Pawn.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_InputFire, Key_Pawn), APawn::StaticClass());
}

void UBTService_InputFire::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	UBlackboardData* BBAsset = GetBlackboardAsset();

	if (ensure(BBAsset))
	{
		Key_Pawn.ResolveSelectedKey(*BBAsset);
	}
}

void UBTService_InputFire::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();

	UObject* Pawn = BBComp->GetValueAsObject(Key_Pawn.SelectedKeyName);

	if (UKismetSystemLibrary::DoesImplementInterface(Pawn, UInputable::StaticClass()))
	{
		IInputable::Execute_Input_AttackPressed(Pawn);
		IInputable::Execute_Input_AttackReleased(Pawn);
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
