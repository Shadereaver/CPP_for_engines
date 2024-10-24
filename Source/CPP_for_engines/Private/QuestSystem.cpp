#include "QuestSystem.h"


UQuestSystem::UQuestSystem()
{
	PrimaryComponentTick.bCanEverTick = false;

	_IsCompleted = false;

	_ActiveQuestIndex = 0;

	FStreamableManager::RequestAsyncLoad(_Quests[_ActiveQuestIndex].);
}


