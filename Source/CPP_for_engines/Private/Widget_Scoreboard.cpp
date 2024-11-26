#include "Widget_Scoreboard.h"

#include "FRunData.h"
#include "Widget_RunEntry.h"
#include "Components/StackBox.h"

void UWidget_Scoreboard::NativeConstruct()
{
	Super::NativeConstruct();

	for (UWidget* Widget : _StackBox->GetAllChildren())
	{
		_Entries.Add(Cast<UWidget_RunEntry>(Widget));
	}
}

void UWidget_Scoreboard::UpdateBoard(FPastRunData &PastRunData)
{
	for (int i = 1; i < 6; i++)
	{
		_Entries[i]->AddData(PastRunData.PastRuns[i - 1].Score, PastRunData.PastRuns[i - 1].Time);
	}
	
	_Entries[6]->AddData(PastRunData.FastestRun.Score, PastRunData.FastestRun.Time);

	_Entries[7]->AddData(PastRunData.HighestScoreRun.Score, PastRunData.HighestScoreRun.Time);
}
