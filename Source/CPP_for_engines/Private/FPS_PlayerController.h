#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPS_PlayerController.generated.h"

struct FInputActionValue;
class UInputAction;

UCLASS()
class CPP_FOR_ENGINES_API AFPS_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _LookAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _MoveAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _JumpAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _AttackAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _AimAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _InteractAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _ReloadAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _SprintAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _CrouchAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _SpecialMovementAction;
	

	virtual void SetupInputComponent() override;

	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void JumpPressed();
	void JumpReleased();
	void AttackPressed();
	void AttackReleased();
	void AimPressed();
	void AimReleased();
	void InteractPressed();
	void ReloadPressed();
	void SprintPressed();
	void SprintReleased();
	void CrouchPressed();
	void CrouchReleased();
	void SpecialMovementPressed();

	virtual void OnPossess(APawn* InPawn) override;
};
