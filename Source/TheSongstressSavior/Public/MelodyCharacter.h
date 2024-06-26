#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "MelodyCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnUseStamina, float Amount, float CurrentStamina, float MaxStamina)

class UStaminaController;


UCLASS()
class THESONGSTRESSSAVIOR_API AMelodyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMelodyCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SetPlayerHUD(UUserWidget* InPlayerHUD);

	bool UseStamina(float stamina);

protected:
	virtual void BeginPlay() override;

	// Made protected for child class 'KingCharacter'
	void LaneChange(float Direction);
	void LaneInterp(float DT);
	FVector LaneEnd, PrevVector = FVector(0, 0, 0);
	int LanePos = 1;
	float LaneLerp = 0.0;
	bool CanChange = true;

private:
	void Move(const FInputActionValue& Value);
	void Jump();

	/* stamina percentage from 0 to 1 */
	void AddStamina(float stamina);
	void ReplenishStamina(float DeltaTime);
	void ConstStaminaLoss(float DeltaTime);

	float LowSpeed = 0.0;
	float RegSpeed = 0.0;

public:

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
	bool MoveInAir = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	float Speed = 10;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* IMC_Input;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = Stamina)
	float MaxStamina = 100;

	UPROPERTY(EditAnywhere, Category = Stamina)
	int RunningStaminaLoss = 2;
	
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

	FOnUseStamina OnUseStamina;

private:

	bool IsRefilling = false;
	bool MoveCancelsReplenish = false;
	bool AlwaysLooseStamina = true;

	float ReplenishDelta = 0.0;
	float LossDelta = 0.0;

	UStaminaController* StaminaController;
	class UMelodyHUD* PlayerHUD;
};