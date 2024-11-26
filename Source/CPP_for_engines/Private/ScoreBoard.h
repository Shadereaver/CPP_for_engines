#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreBoard.generated.h"

class UWidget_Scoreboard;
class UWidgetComponent;

UCLASS()
class CPP_FOR_ENGINES_API AScoreBoard : public AActor
{
	GENERATED_BODY()

public:
	AScoreBoard();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> _Scoreboard;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidget_Scoreboard> _ScoreboardRef;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateScoreboard(FPastRunData &PastRunData);
};
