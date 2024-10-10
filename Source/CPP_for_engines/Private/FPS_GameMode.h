#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FPS_GameMode.generated.h"

class UGameRule;

UCLASS(Abstract)
class CPP_FOR_ENGINES_API AFPS_GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	
protected:
	TArray<TObjectPtr<AActor>> _PlayerStarts;
	FTimerHandle _TimerDecreaseCountdown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<AController>> _Controllers;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Match management", meta=(ClampMin=1))
	int _CountdownTimer = 1;
	UPROPERTY(EditAnywhere, Category="Match management")
	TSubclassOf<APawn> _MatchPawn;

	int _GamRulesLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UGameRule>> _GameRuleManagers;
	
	UFUNCTION()
	void DecreaseCountdown();

	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;
	virtual void OnMatchStateSet() override;

	virtual bool ReadyToStartMatch_Implementation() override;
	virtual bool ReadyToEndMatch_Implementation() override;

private:
	UFUNCTION()
	void Handle_GameRuleComplete();
	UFUNCTION()
	void Handle_GameRulePointsScored(AController* Scorer, int Points);
};
