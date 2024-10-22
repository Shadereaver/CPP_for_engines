#pragma once

#include "CoreMinimal.h"
#include "Inputable.h"
#include "GameFramework/Character.h"
#include "FPS_Player.generated.h"

class UBehaviorTree;
class AWeaponBase;
class UHealthComponent;
class UCharacterMovementComponent;
class UCameraComponent;


UCLASS(Abstract)
class CPP_FOR_ENGINES_API AFPS_Player : public ACharacter, public IInputable
{
	GENERATED_BODY()

public:
	AFPS_Player();

	virtual void Input_Look_Implementation(FVector2D Value) override;
	virtual void Input_Move_Implementation(FVector2D Value) override;
	virtual void Input_AttackPressed_Implementation() override;
	virtual void Input_AttackReleased_Implementation() override;
	virtual void Input_JumpPressed_Implementation() override;
	virtual void Input_JumpReleased_Implementation() override;
	virtual void Input_AimPressed_Implementation() override;
	virtual void Input_AimReleased_Implementation() override;
	virtual void Input_Interact_Implementation() override;
	virtual void Input_Reload_Implementation() override;
	virtual void Input_CrouchPressed_Implementation() override;
	virtual void Input_CrouchReleased_Implementation() override;
	virtual void Input_SpacialMovementPressed_Implementation() override;
	virtual void Input_SprintPressed_Implementation() override;
	virtual void Input_SprintReleased_Implementation() override;

	virtual void BeginPlay() override;

	virtual UInputMappingContext* GetMappingContext_Implementation() override;
	virtual UBehaviorTree* GetBehaviorTree_Implementation() override;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> _Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSprinting;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _WeaponAttachPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeaponBase> _DefaultWeapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AWeaponBase> _WeaponRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> _InputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBehaviorTree> _BeaviorTree;

private:
	UFUNCTION()
	void Handle_HealthDead(AController* Causer);
	UFUNCTION()
	void Handle_HealthDamaged(float Ratio);
};
