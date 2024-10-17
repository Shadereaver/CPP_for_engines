#include "FPS_GameMode.h"

#include "Controllerable.h"
#include "GameRule.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

AActor* AFPS_GameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if (_PlayerStarts.Num() == 0)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
		for (AActor* Actor : FoundActors)
		{
			_PlayerStarts.Add(Actor);
		}
	}
	if (_PlayerStarts.Num() > 0)
	{
		return _PlayerStarts[FMath::RandRange(0, _PlayerStarts.Num() - 1)];
	}
	return nullptr;
}

void AFPS_GameMode::PostLogin(APlayerController* NewPlayer)
{
	_Controllers.AddUnique(NewPlayer);
	Super::PostLogin(NewPlayer);
}

void AFPS_GameMode::Logout(AController* Exiting)
{
	_Controllers.Remove(Exiting);
	Super::Logout(Exiting);
}

void AFPS_GameMode::HandleMatchIsWaitingToStart()
{
	TArray<UActorComponent*> OutComponents;

	GetComponents(OutComponents);

	for (UActorComponent* Comp : OutComponents)
	{
		if (UGameRule* Rule = Cast<UGameRule>(Comp))
		{
			_GameRuleManagers.Add(Rule);
			Rule->Init();

			Rule->OnComplete.AddUniqueDynamic(this, &AFPS_GameMode::Handle_GameRuleComplete);
			Rule->OnPointsScored.AddUniqueDynamic(this, &AFPS_GameMode::Handle_GameRulePointsScored);

			_GamRulesLeft++;
		}
	}
	
	GetWorld()->GetTimerManager().SetTimer(_TimerDecreaseCountdown, this, &AFPS_GameMode::DecreaseCountdown, 1.f, false);
	Super::HandleMatchIsWaitingToStart();
}

void AFPS_GameMode::HandleMatchHasStarted()
{
	DefaultPawnClass = _MatchPawn;
	for(AController* Controller : _Controllers)
	{
		RestartPlayer(Controller);
	}
	Super::HandleMatchHasStarted();
}

void AFPS_GameMode::HandleMatchHasEnded()
{
	Super::HandleMatchHasEnded();
}

void AFPS_GameMode::OnMatchStateSet()
{
	FString Output;

	if (MatchState == MatchState::WaitingToStart)
	{
		Output = "Waiting to start";
	}
	else if (MatchState == MatchState::InProgress)
	{
		Output = "Match in progress";
	}
	else if (MatchState == MatchState::WaitingPostMatch)
	{
		Output = "Waiting post match";
	}
	else if (MatchState == MatchState::EnteringMap)
	{
		Output = "Entering map";
	}
	else if (MatchState == MatchState::LeavingMap)
	{
		Output = "Leaving map";
	}
	else if (MatchState == MatchState::Aborted)
	{
		Output = "Match aborted";
	}

	UE_LOG(LogTemp, Display, TEXT("MATCH STATE CHANGED: %s"), *Output);
	
	Super::OnMatchStateSet();
}

bool AFPS_GameMode::ReadyToStartMatch_Implementation()
{
	return false;
}

bool AFPS_GameMode::ReadyToEndMatch_Implementation()
{
	return false;
}

void AFPS_GameMode::Handle_GameRuleComplete()
{
}

void AFPS_GameMode::Handle_GameRulePointsScored(AController* Scorer, int Points)
{
	if (UKismetSystemLibrary::DoesImplementInterface(Scorer, UControllerable::StaticClass()))
	{
		IControllerable::Execute_AddPoints(Scorer, Points);
	}
}

void AFPS_GameMode::DecreaseCountdown()
{
	_CountdownTimer--;
	UE_LOG(LogTemp, Display, TEXT("GAMEMODE COUNTDOWN: %d"), _CountdownTimer);
	if (_CountdownTimer <= 0)
	{
		StartMatch();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(_TimerDecreaseCountdown, this, &AFPS_GameMode::DecreaseCountdown, 1.f, false);
	}
}
