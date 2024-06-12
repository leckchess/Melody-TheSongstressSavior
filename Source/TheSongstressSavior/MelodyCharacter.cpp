#include "MelodyCharacter.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

AMelodyCharacter::AMelodyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = true;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
}

void AMelodyCharacter::BeginPlay()
{
	Super::BeginPlay();

	LanePos = (LaneCount + 1) / 2;

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Input, 0);
		}
	}
	
}

void AMelodyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (AutoForward)
	{
		const FVector CurrentVector = GetActorLocation();
		SetActorLocation(CurrentVector + FVector(Speed, 0, 0));
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

		// Move and Look at stuff
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMelodyCharacter::Move);
		//EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMelodyCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Woops... Failed to grab the Enhanced Input component silly goose!"));
	}

}

void AMelodyCharacter::LaneChange(float Direction)
{
	FVector CurVec = GetActorLocation();
	if (LanePos > 1 && Direction < 0)
	{
		LanePos--;
		SetActorLocation(CurVec + FVector(0, -LaneSize, 0));
	}
	else if (LanePos < LaneCount && Direction > 0)
	{
		LanePos++;
		SetActorLocation(CurVec + FVector(0, LaneSize, 0));
	}
}

void AMelodyCharacter::Move(const FInputActionValue& MoveValue)
{
	FVector2D MoveVector = MoveValue.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Grabs the rotation of the controller
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Gets the forward direction based on rotation
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		//AddMovementInput(ForwardDirection, MoveVector.Y);
		//AddMovementInput(RightDirection, MoveVector.X);
		if (MoveVector.X != 0)
		{
			AMelodyCharacter::LaneChange(MoveVector.X);
		}
	}
}

/* void AMelodyCharacter::Look(const FInputActionValue& LookValue)
{
	FVector2D LookVector = LookValue.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
} */