#include "FPS_GameMode.h"

#include "Controllerable.h"
#include "GameRule.h"
#include "PlayerDeathEvent.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "JsonObjectConverter.h"

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
	if (UKismetSystemLibrary::DoesImplementInterface(NewPlayer, UPlayerDeathEvent::StaticClass()))
	{
		IPlayerDeathEvent* INewPlayer = Cast<IPlayerDeathEvent>(NewPlayer);
		INewPlayer->GetPlayerDeathDelegate().AddUniqueDynamic(this, &AFPS_GameMode::Handle_playerDeath);
	}
	
	_Controllers.AddUnique(NewPlayer);
	Super::PostLogin(NewPlayer);
}

void AFPS_GameMode::Logout(AController* Exiting)
{
	_Controllers.Remove(Exiting);
	Super::Logout(Exiting);
}

void AFPS_GameMode::StartTimer_Implementation()
{
	GetWorldTimerManager().SetTimer(_GameTimer, this, &AFPS_GameMode::IncreaseTime, 0.1f, true);
}

FGameModeRunDataUpdateSignature& AFPS_GameMode::GetRunDataDelegate()
{
	return OnRunDataUpdate;
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

			_GameRulesLeft++;
		}
	}
	
	GetWorldTimerManager().SetTimer(_TimerDecreaseCountdown, this, &AFPS_GameMode::DecreaseCountdown, 1.f, false);
	Super::HandleMatchIsWaitingToStart();
}

void AFPS_GameMode::HandleMatchHasStarted()
{
	OnRunDataUpdate.Broadcast(_PastRunData);
	DefaultPawnClass = _MatchPawn;
	_RunData.Time = 0;
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

void AFPS_GameMode::BeginPlay()
{
	Super::BeginPlay();
	_PastRunData = FPastRunData();
	FString File = FPaths::ProjectDir();
	File.Append(TEXT("PrevRuns.txt"));

	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	FString StringToSave;

	if (FileManager.FileExists(*File))
	{
		if (FFileHelper::LoadFileToString(StringToSave, *File))
		{
			FJsonObjectConverter::JsonObjectStringToUStruct(StringToSave, &_PastRunData, 0, 0);
			UE_LOG(LogTemp, Warning, TEXT("File Loaded"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("File not loaded"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("File : %s : not found"), *File);
	}
}

void AFPS_GameMode::Handle_GameRuleComplete()
{
	_GameRulesLeft--;
	if (_GameRulesLeft == 0)
	{
		
		Save();
		GetWorldTimerManager().SetTimer(_RestartTimer, this, &AFPS_GameMode::Restart, 3);
	}
}

void AFPS_GameMode::Handle_GameRulePointsScored(AController* Scorer, int Points)
{
	if (UKismetSystemLibrary::DoesImplementInterface(Scorer, UControllerable::StaticClass()))
	{
		_RunData.Score += Points;
		IControllerable::Execute_AddPoints(Scorer, _RunData.Score);
	}
}

void AFPS_GameMode::Handle_playerDeath(AController* Causer)
{
	Save();
	GetWorldTimerManager().SetTimer(_RestartTimer, this, &AFPS_GameMode::Restart, 3);
}

void AFPS_GameMode::Save()
{
	GetWorldTimerManager().ClearTimer(_GameTimer);
	_PastRunData.AddRun(_RunData);
	
	FString File = FPaths::ProjectDir();
	File.Append(TEXT("PrevRuns.txt"));

	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	FString StringToSave;

	FJsonObjectConverter::UStructToJsonObjectString(_PastRunData, StringToSave);

	if (FileManager.FileExists(*File))
	{
		if (FFileHelper::SaveStringToFile(StringToSave, *File))
		{
			OnRunDataUpdate.Broadcast(_PastRunData);
			UE_LOG(LogTemp, Warning, TEXT("File saved"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("File not saved"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("File : %s : not found"), *File);
	}
}

void AFPS_GameMode::Restart()
{
	RestartGame();
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

void AFPS_GameMode::IncreaseTime()
{
	_RunData.Time += 0.1;
}

