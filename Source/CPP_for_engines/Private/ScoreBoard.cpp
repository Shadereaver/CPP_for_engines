#include "ScoreBoard.h"

#include "RunDataInterface.h"
#include "Widget_Scoreboard.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


AScoreBoard::AScoreBoard()
{
	PrimaryActorTick.bCanEverTick = false;

	_Scoreboard = CreateDefaultSubobject<UWidgetComponent>(TEXT("_Scoreboard"));
	_Scoreboard->SetupAttachment(RootComponent);
}

void AScoreBoard::BeginPlay()
{
	Super::BeginPlay();

	TObjectPtr<AGameMode> GameMode = Cast<AGameMode>(UGameplayStatics::GetGameMode(this));

	if (UKismetSystemLibrary::DoesImplementInterface(GameMode, URunDataInterface::StaticClass()))
	{
		IRunDataInterface* IGameMode = Cast<IRunDataInterface>(GameMode);
		IGameMode->GetRunDataDelegate().AddUniqueDynamic(this, &AScoreBoard::UpdateScoreboard);
	}

	_ScoreboardRef = Cast<UWidget_Scoreboard>(_Scoreboard->GetWidget());
}

void AScoreBoard::UpdateScoreboard(FPastRunData& PastRunData)
{
	_ScoreboardRef->UpdateBoard(PastRunData);
}
