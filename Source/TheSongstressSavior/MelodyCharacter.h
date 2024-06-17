#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "MelodyCharacter.generated.h"

class UStaminaController;

UCLASS()
class THESONGSTRESSSAVIOR_API AMelodyCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UStaminaController* StaminaController;

public:
	// Sets default values for this character's properties
	AMelodyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Lane Options")
	int LaneCount = 2;

	UPROPERTY(EditAnywhere, Category = "Lane Options")
	int SetStartingLane = -1;

	UPROPERTY(EditAnywhere, Category = "Lane Options")
	float LaneSize = 200;

	UPROPERTY(EditAnywhere, Category = "Lane Options")
	float LaneChangeSpeed = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	bool AutoForward = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	float Speed = 10;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* IMC_Input;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = Stamina)
	float MaxStamina;
	
	UPROPERTY(EditAnywhere, Category = Stamina)
	bool bMovementAffectsStamina;
	UPROPERTY(EditAnywhere, Category = Stamina, meta=(EditCondition="bMovementAffectsStamina", EditConditionHides))
	float MovementStaminaCost;

	UPROPERTY(EditAnywhere, Category = Stamina)
	bool bJumpAffectsStamina;
	UPROPERTY(EditAnywhere, Category = Stamina, meta=(EditCondition="bJumpAffectsStamina", EditConditionHides))
	float JumpStaminaCost;

	UPROPERTY(EditAnywhere, Category = Stamina)
	bool bSwitchingLaneAffectsStamina;
	UPROPERTY(EditAnywhere, Category = Stamina, meta=(EditCondition="bSwitchingLaneAffectsStamina", EditConditionHides))
	float SwitchingLaneStaminaCost;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Move(const FInputActionValue& Value);
	void LaneChange(float Direction);
	void LaneInterp(float Alpha);

	/**
	 * 
	 * @param stamina stamina percentage from 0 to 1
	 */
	void AddStamina(float stamina);

	// Lane Variables
	FVector LaneEnd, PrevVector = FVector(0, 0, 0);
	int LanePos = 1;
	float LaneLerp = 0.0;
	bool CanChange = true;
};
