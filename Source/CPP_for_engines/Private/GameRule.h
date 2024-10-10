﻿#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameRule.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameRuleCompleteSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameRulePointsScoredSignature, AController*, Scorer, int, points);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CPP_FOR_ENGINES_API UGameRule : public UActorComponent
{
	GENERATED_BODY()

public:
	UGameRule();

	FGameRuleCompleteSignature OnComplete;
	FGameRulePointsScoredSignature OnPointsScored;

	UFUNCTION()
	virtual void Init();

protected:
	void BroadcastComplete();
	void BroadcastPointsScored(AController* Scorer, int Points);
};
