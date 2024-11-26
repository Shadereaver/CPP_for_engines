#include "Widget_EnemyHealthBar.h"

#include "Components/ProgressBar.h"

void UWidget_EnemyHealthBar::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidget_EnemyHealthBar::UpdateHealth(float NewHealthRatio)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(NewHealthRatio);
	}
}
