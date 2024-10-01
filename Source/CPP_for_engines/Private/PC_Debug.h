#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_Debug.generated.h"

struct FInputActionValue;
class UInputAction;

UCLASS()
class CPP_FOR_ENGINES_API APC_Debug : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<UInputAction> _DebugAction;

	virtual void SetupInputComponent() override;

	void Debug(const FInputActionValue& Value);
};
