#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Inputable.generated.h"

UINTERFACE()
class UInputable : public UInterface
{
	GENERATED_BODY()
};

class UInputMappingContext;

class CPP_FOR_ENGINES_API IInputable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Look(FVector2D Value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Move(FVector2D Value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_JumpPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_JumpReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_AttackPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_AttackReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Interact();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_AimPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_AimReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Reload();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_SprintPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_SprintReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_CrouchPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_CrouchReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_SpacialMovmentPressed();

	//TODO:: more movement

	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UInputMappingContext* GetMappingContext();
};
