#pragma once

#include "FRunData.generated.h"

USTRUCT()
struct FRunData
{
	GENERATED_BODY()

	UPROPERTY()
	float Time;
	UPROPERTY()
	int Score;
};

USTRUCT()
struct FPastRunData
{
	GENERATED_BODY()
	
	UPROPERTY()
	FRunData FastestRun;
	UPROPERTY()
	FRunData HighestScoreRun;
	UPROPERTY()
	TArray<FRunData> PastRuns;
	UPROPERTY()
	int LastrunIndex;

	FPastRunData()
	{
		FastestRun.Score = 0;
		FastestRun.Time = 0;
		HighestScoreRun.Score = 0;
		HighestScoreRun.Time = 0;
		LastrunIndex = 0;

		PastRuns.Init(FastestRun, 5);
	}

	void AddRun(FRunData RunData)
	{
		PastRuns[LastrunIndex] = RunData;
		LastrunIndex++;
		if (LastrunIndex == 5)
		{
			LastrunIndex = 0;
		}

		if (FastestRun.Time <= RunData.Time)
		{
			FastestRun = RunData;
		}
		if (HighestScoreRun.Score <= RunData.Score)
		{
			HighestScoreRun = RunData;
		}
	}
};
