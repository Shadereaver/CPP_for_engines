#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Scoreboard.generated.h"

class UWidget_RunEntry;
struct FPastRunData;
class UStackBox;

UCLASS()
class CPP_FOR_ENGINES_API UWidget_Scoreboard : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateBoard(FPastRunData &PastRunData);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UStackBox> _StackBox;

	UPROPERTY()
	TArray<UWidget_RunEntry*> _Entries;
};
