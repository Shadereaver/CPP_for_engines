#include "Widget_RunEntry.h"
#include "Components/TextBlock.h"

void UWidget_RunEntry::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidget_RunEntry::AddData(int Score, float Time)
{
	_Score->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), Score)));
	_Time->SetText(FText::FromString(FString::Printf(TEXT("Time: %fs"), Time)));
}
