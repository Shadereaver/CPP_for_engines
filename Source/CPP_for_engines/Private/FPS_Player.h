#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Inputable.h"
#include "NavLinkInterface.h"
#include "PawnOnDamageEvent.h"
#include "WeaponPickupInterface.h"
#include "GameFramework/Character.h"
#include "FPS_Player.generated.h"

class UWidget_EnemyHealthBar;
class UWidgetComponent;
class UBehaviorTree;
class AWeaponBase;
class UHealthComponent;
class UCharacterMovementComponent;
class UCameraComponent;



UCLASS(Abstract)
class CPP_FOR_ENGINES_API AFPS_Player : public ACharacter, public IInputable, public IPawnOnDamageEvent,
public INavLinkInterface, public IGenericTeamAgentInterface, public IWeaponPickupInterface
{
	GENERATED_BODY()

public:
	AFPS_Player();

	FPawnDamagedSignature OnDamaged;
	FPawnDeathSignature OnDeath;
	FNavLinkInterfaceResumePathSignature OnResume;

	virtual FPawnDamagedSignature& GetDamageDelegate() override;
	virtual FPawnDeathSignature& GetDeathDelegate() override;
	virtual void RequestHealthUpdate() override;

	virtual void Input_Look_Implementation(FVector2D Value) override;
	virtual void Input_Move_Implementation(FVector2D Value) override;
	virtual void Input_AttackPressed_Implementation() override;
	virtual void Input_AttackReleased_Implementation() override;
	virtual void Input_JumpPressed_Implementation() override;
	virtual void Input_JumpReleased_Implementation() override;
	virtual void Input_CrouchPressed_Implementation() override;
	virtual void Input_CrouchReleased_Implementation() override;
	virtual void Input_SpacialMovementPressed_Implementation() override;
	virtual void Input_SprintPressed_Implementation() override;
	virtual void Input_SprintReleased_Implementation() override;

	virtual void BeginPlay() override;

	virtual UInputMappingContext* GetMappingContext_Implementation() override;
	virtual UBehaviorTree* GetBehaviorTree_Implementation() override;
	
	virtual FNavLinkInterfaceResumePathSignature& GetResumeDelegate() override;
	virtual void StartWallRun(const FVector& DestinationPoint) override;

	virtual FGenericTeamId GetGenericTeamId() const override;

	virtual void ChangeWeapon_Implementation(TSubclassOf<AWeaponBase> Weapon) override;

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> _Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool _bIsSprinting;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _WalkSpeedRatio;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool _bIsWallRunning;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool _bIsMovingSpecial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _WeaponAttachPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeaponBase> _DefaultWeapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AWeaponBase> _WeaponRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> _InputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBehaviorTree> _BehaviorTree;

	UPROPERTY(EditAnywhere)
	FGenericTeamId _TeamId;

	FTimerHandle _TimerWallRunUpdate;
	FTimerHandle _TimerAIWallRunUpdate;
	FTimerHandle _TimerAIWallRunLimit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool _bIsRightWallRun;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool _bHasWallJumped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UWidgetComponent> _HealthBar;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidget_EnemyHealthBar> _HealthBarRef;

	FTimerHandle _DeathTimer;
	
	UFUNCTION()
	virtual void Landed(const FHitResult& Hit) override;
	
private:
	UFUNCTION()
	void Handle_HealthDead(AController* Causer);
	UFUNCTION()
	void Handle_HealthDamaged(float Ratio);
	
	UFUNCTION()
	void WallRun();
	UFUNCTION()
	void AIWallRun(FVector Dest);

	void WallrunReset();

	void ResumeNav();

	UFUNCTION()
	void Death();
};
