#include "MelodyCharacter.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "StaminaController.h"
#include "GameFramework/CharacterMovementComponent.h"

AMelodyCharacter::AMelodyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = true;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	StaminaController = NewObject<UStaminaController>();
	
}

void AMelodyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set initial lane to median
	LanePos = (LaneCount + 1) / 2;
	if (SetStartingLane >= 1 && SetStartingLane <= LaneCount)
	{
		// Set custom start if SetStartingLane is valid
		int Adjust = SetStartingLane - LanePos;
		LanePos = SetStartingLane;

		SetActorLocation(GetActorLocation() + FVector(0, LaneSize * Adjust, 0));
	}
	else if (SetStartingLane != -1)
	{
		UE_LOG(LogTemp, Error, TEXT("MELODYCHARACTER | 'SetStartingLane' is invalid."));
	}

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Input, 0);
		}
	}

	StaminaController->Initialize(MaxStamina);
}

void AMelodyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (AutoForward)
	{
		// Constantly move the player forward
		const FVector CurrentVector = GetActorLocation();
		SetActorLocation(CurrentVector + FVector(Speed, 0, 0));
	}

	if (!CanChange)
	{
		// runs when lane change has initiated
		LaneLerp = LaneLerp + LaneChangeSpeed * DeltaTime;
		AMelodyCharacter::LaneInterp(LaneLerp);
		if (LaneLerp >= 1)
		{
			CanChange = true;
			LaneLerp = 0.0;
			PrevVector = FVector(0, 0, 0);
		}
	}
}

void AMelodyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Action bindings
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Do a jump
		EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Move
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMelodyCharacter::Move);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Woops... Failed to grab the Enhanced Input component silly goose!"));
	}
}

void AMelodyCharacter::LaneInterp(float Alpha)
{
	FVector Dest = FMath::InterpEaseOut(FVector(0, 0, 0), LaneEnd, Alpha, 2);
	SetActorLocation(GetActorLocation() + Dest - PrevVector);
	PrevVector = Dest;
}

void AMelodyCharacter::AddStamina(float stamina)
{
	StaminaController->AddStaminaPercentage(stamina);
}

void AMelodyCharacter::LaneChange(float Direction)
{
	if (!CanChange || GetCharacterMovement()->IsFalling()) return;

	LaneEnd = FVector(0, LaneSize * Direction, 0);
	if (LanePos > 1 && Direction < 0)
	{
		if (!bSwitchingLaneAffectsStamina || StaminaController->UseStamina(SwitchingLaneStaminaCost))
		{
			// Move Left
			LanePos--;

			CanChange = false;
		}
	}
	else if (LanePos < LaneCount && Direction > 0)
	{
		if (!bSwitchingLaneAffectsStamina || StaminaController->UseStamina(SwitchingLaneStaminaCost))
		{
			// Move Right
			LanePos++;
			CanChange = false;
		}
	}
}

void AMelodyCharacter::Move(const FInputActionValue& MoveValue)
{
	FVector2D MoveVector = MoveValue.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (MoveVector.X != 0)
		{
			AMelodyCharacter::LaneChange(MoveVector.X);
		}
	}
}
