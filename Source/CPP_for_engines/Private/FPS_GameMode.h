#pragma once

#include "CoreMinimal.h"
#include "FRunData.h"
#include "RunDataInterface.h"
#include "StartGameTimer.h"
#include "GameFramework/GameMode.h"
#include "FPS_GameMode.generated.h"

class UGameRule;

UCLASS(Abstract)
class CPP_FOR_ENGINES_API AFPS_GameMode : public AGameMode, public IStartGameTimer, public IRunDataInterface
{
	GENERATED_BODY()

public:
	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	virtual void StartTimer_Implementation() override;

	FGameModeRunDataUpdateSignature OnRunDataUpdate;
	virtual FGameModeRunDataUpdateSignature& GetRunDataDelegate() override;

protected:
	TArray<TObjectPtr<AActor>> _PlayerStarts;
	FTimerHandle _TimerDecreaseCountdown;

	FTimerHandle _GameTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<AController>> _Controllers;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Match management", meta=(ClampMin=1))
	int _CountdownTimer = 1;
	UPROPERTY(EditAnywhere, Category="Match management")
	TSubclassOf<APawn> _MatchPawn;

	int _GameRulesLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UGameRule>> _GameRuleManagers;

	FRunData _RunData;
	FPastRunData _PastRunData;

	FTimerHandle _RestartTimer;
	
	UFUNCTION()
	void DecreaseCountdown();

	UFUNCTION()
	void IncreaseTime();

	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;
	virtual void OnMatchStateSet() override;

	virtual bool ReadyToStartMatch_Implementation() override;
	virtual bool ReadyToEndMatch_Implementation() override;

	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void Handle_GameRuleComplete();
	UFUNCTION()
	void Handle_GameRulePointsScored(AController* Scorer, int Points);

	UFUNCTION()
	void Handle_playerDeath(AController* Causer);

	UFUNCTION()
	void Save();

	UFUNCTION()
	void Restart();
};
