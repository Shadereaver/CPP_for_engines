#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/StreamableManager.h"
#include "QuestSystem.generated.h"

class UQuest;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CPP_FOR_ENGINES_API UQuestSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	UQuestSystem();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UQuest>> _Quests;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int _ActiveQuestIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool _IsCompleted;
	
	TObjectPtr<FStreamableHandle> StreamableHandle;
};
