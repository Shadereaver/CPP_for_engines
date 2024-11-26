#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_RunEntry.generated.h"

class UTextBlock;

UCLASS()
class CPP_FOR_ENGINES_API UWidget_RunEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void AddData(int Score, float Time);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> _Score;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> _Time;
};
