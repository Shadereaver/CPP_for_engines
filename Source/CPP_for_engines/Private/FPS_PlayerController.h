#pragma once

#include "CoreMinimal.h"
#include "Controllerable.h"
#include "PlayerDeathEvent.h"
#include "GameFramework/PlayerController.h"
#include "FPS_PlayerController.generated.h"

class UWidget_HUD;
struct FInputActionValue;
class UInputAction;

UCLASS(Abstract)
class CPP_FOR_ENGINES_API AFPS_PlayerController : public APlayerController, public IControllerable, public IPlayerDeathEvent
{
	GENERATED_BODY()
	
public:
	FPlayerDeathSignature OnPlayerDeath;
	
	virtual FPlayerDeathSignature& GetPlayerDeathDelegate() override;

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
	TObjectPtr<UInputAction> _SprintAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _CrouchAction;
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> _SpecialMovementAction;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidget_HUD> _HUDWidgetClass;
	TObjectPtr<UWidget_HUD> _HUDWidget;

	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void JumpPressed();
	void JumpReleased();
	void AttackPressed();
	void AttackReleased();
	void SprintPressed();
	void SprintReleased();
	void CrouchPressed();
	void CrouchReleased();
	void SpecialMovementPressed();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	virtual void AddPoints_Implementation(int Points) override;

	UFUNCTION()
	void Handle_OnDamage(float Ratio);

	UFUNCTION()
	void Handle_OnDeath(AController* Causer);
};
