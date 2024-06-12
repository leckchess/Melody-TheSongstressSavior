#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "MelodyCharacter.generated.h"

UCLASS()
class THESONGSTRESSSAVIOR_API AMelodyCharacter : public ACharacter
{
	GENERATED_BODY()

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
	float LaneSize = 200;

	UPROPERTY(EditAnywhere, Category = "Lane Options")
	float LaneChangeSpeed = 3;

	UPROPERTY(EditAnywhere, Category = Input)
	bool AutoForward = true;

	UPROPERTY(EditAnywhere, Category = Input)
	float Speed = 10;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* IMC_Input;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveAction;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void Move(const FInputActionValue& Value);
	void LaneChange(float Direction, bool Ready);
	void LaneInterp(float Alpha);

	// Lane Variables
	FVector LaneEnd, PrevVector = FVector(0, 0, 0);
	int LanePos = 2;
	float LaneLerp = 0.0;
	bool CanChange = true;

};