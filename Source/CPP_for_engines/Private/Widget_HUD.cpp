#include "Widget_HUD.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UWidget_HUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (HealthBar) {HealthBar->SetPercent(0.f);}
	if (ScoreText) {ScoreText->SetText(FText::FromString("Score: idk"));}
}

void UWidget_HUD::UpdateHealth(float NewHealthRatio)
{
		if (HealthBar) {HealthBar->SetPercent(NewHealthRatio);}
}

void UWidget_HUD::UpdateScore(int NewScore)
{
	if (ScoreText) {ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), NewScore)));}
}
