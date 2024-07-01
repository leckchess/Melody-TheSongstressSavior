#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "InputMappingContext.h"
#include "DynamicSoundSystem.h"
#include "MelodyCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnUseStamina, float Amount, float CurrentStamina, float MaxStamina)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUpdateSpeed, float CurrentSpeed, float MaxSpeed)

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
	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintCallable)
	void SetPlayerHUD(UUserWidget* InPlayerHUD);

	/* stamina percentage from 0 to 1 */
	void AddStamina(float stamina);
	bool UseStamina(float stamina);
	// Positive or negative InSpeed will be added to current Speed
	float UpdateSpeed(float InSpeed);

	UFUNCTION()
	void OnUseStaminaHandle(float Amount, float InCurrentStamina, float InMaxStamina);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
	UFUNCTION()
	void StartGame();

	void OnCollectToken();

	void ActivateMusicalMood(Mood MusicalMood);

	float LowSpeed = 0.0;
	float RegSpeed = 0.0;

protected:
	virtual void BeginPlay() override;

	// Made protected for child class 'KingCharacter'
	void LaneChange(float Direction);
	void LaneInterp(float DT);

private:
	void Move(const FInputActionValue& Value);
	void Jump();

	void ReplenishStamina(float DeltaTime);
	void ConstStaminaLoss(float DeltaTime);

	class ADynamicSoundSystem* GetAudioSystem();

	UFUNCTION()
	void OnShowNotificationHandle();

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
	bool AutoForward = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	bool MoveInAir = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	float Speed = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxSpeed = 30;

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

	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	class UCapsuleComponent* TriggerCapsule;

	FOnUseStamina OnUseStamina;
	FOnUpdateSpeed OnUpdateSpeed;

protected:
	FVector LaneEnd, PrevVector = FVector(0, 0, 0);
	int LanePos = 1;
	float LaneLerp = 0.0;
	bool CanChange = true;

	class ADynamicSoundSystem* CachedAudioSystem;

private:
	bool IsRefilling = false;
	bool MoveCancelsReplenish = false;
	bool AlwaysLooseStamina = true;

	float ReplenishDelta = 0.0;
	float LossDelta = 0.0;

	UStaminaController* StaminaController;
	class UMelodyHUD* PlayerHUD;
};