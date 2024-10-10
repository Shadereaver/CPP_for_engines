#include "GameRule.h"


UGameRule::UGameRule()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UGameRule::Init()
{
}

void UGameRule::BroadcastComplete()
{
	OnComplete.Broadcast();
}

void UGameRule::BroadcastPointsScored(AController* Scorer, int Points)
{
	OnPointsScored.Broadcast(Scorer, Points);
}

