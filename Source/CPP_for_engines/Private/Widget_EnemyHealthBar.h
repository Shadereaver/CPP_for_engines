#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_EnemyHealthBar.generated.h"

class UProgressBar;

UCLASS()
class CPP_FOR_ENGINES_API UWidget_EnemyHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateHealth(float NewHealthRatio);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
};
