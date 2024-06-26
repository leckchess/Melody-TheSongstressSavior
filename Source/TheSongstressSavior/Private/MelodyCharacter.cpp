#include "MelodyCharacter.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StaminaController.h"
#include "MelodyHUD.h"
#include "Token.h"

AMelodyCharacter::AMelodyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = true;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->GravityScale = 2.2;
	GetCharacterMovement()->JumpZVelocity = 900;

	StaminaController = NewObject<UStaminaController>();
	
	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(55.f, 96.0f);;
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AMelodyCharacter::OnOverlapBegin);
}

void AMelodyCharacter::BeginPlay()
{
	Super::BeginPlay();

	LowSpeed = Speed * 0.75;
	RegSpeed = Speed;

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
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) 
		{
			Subsystem->AddMappingContext(IMC_Input, 0);
		}
	}
	
	if (StaminaController)
	{
		StaminaController->Initialize(MaxStamina);
	}
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

	AMelodyCharacter::LaneInterp(DeltaTime);
	AMelodyCharacter::ReplenishStamina(DeltaTime);
}

void AMelodyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Action bindings
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Do a jump
		EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &AMelodyCharacter::Jump);
		EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Move
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMelodyCharacter::Move);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Woops... Failed to grab the Enhanced Input component silly goose!"));
	}

}

void AMelodyCharacter::SetPlayerHUD(UUserWidget* InPlayerHUD)
{
	PlayerHUD = Cast<UMelodyHUD>(InPlayerHUD);

	if (PlayerHUD)
	{
		PlayerHUD->InitHUD(this);

		if(StaminaController)
		{
			OnUseStamina.Broadcast(0.f, StaminaController->GetCurrentStamina(), StaminaController->GetMaxStamina());
		}
	}
}

void AMelodyCharacter::LaneInterp(float DT)
{
	if (CanChange) return;
	LaneLerp = LaneLerp + LaneChangeSpeed * DT;
	FVector Dest = FMath::InterpEaseOut(FVector(0, 0, 0), LaneEnd, LaneLerp, 2);
	SetActorLocation(GetActorLocation() + Dest - PrevVector);
	PrevVector = Dest;
	if (LaneLerp >= 1)
	{
		CanChange = true;
		LaneLerp = 0.0;
		PrevVector = FVector(0, 0, 0);
	}
}

void AMelodyCharacter::ReplenishStamina(float DeltaTime)
{
	if (IsRefilling || StaminaController->GetCurrentStamina() <= 0)
	{
		Speed = LowSpeed;
		IsRefilling = true;
		DeltaSeconds = DeltaSeconds + (1 * DeltaTime);
		if (DeltaSeconds > 0.15)
		{
			AMelodyCharacter::AddStamina(0.02);
			DeltaSeconds = 0;
		}
		if (StaminaController->GetCurrentStamina() == 100)
		{
			Speed = RegSpeed;
			IsRefilling = false;
		}
	}
}

bool AMelodyCharacter::UseStamina(float stamina)
{
	if (StaminaController == nullptr) { return true; }

	if (StaminaController->UseStamina(stamina))
	{
		if (MoveCancelsReplenish) { IsRefilling = false; }
		OnUseStamina.Broadcast(stamina, StaminaController->GetCurrentStamina(), StaminaController->GetMaxStamina());
		return true;
	}

	return false;
}

void AMelodyCharacter::AddStamina(float stamina)
{
	StaminaController->AddStaminaPercentage(stamina);
	OnUseStamina.Broadcast(stamina, StaminaController->GetCurrentStamina(), StaminaController->GetMaxStamina());
}

void AMelodyCharacter::LaneChange(float Direction)
{
	if (!CanChange || !MoveInAir && GetCharacterMovement()->IsFalling()) return;
	LaneEnd = FVector(0, LaneSize * Direction, 0);

	if (Direction < 0 && LanePos > 1)
	{
		if (!bSwitchingLaneAffectsStamina || UseStamina(SwitchingLaneStaminaCost))
		{
			// Move Left
			LanePos--;
			CanChange = false;
		}
	}
	else if (Direction > 0 && LanePos < LaneCount)
	{
		if (!bSwitchingLaneAffectsStamina || UseStamina(SwitchingLaneStaminaCost))
		{
			// Move Right
			LanePos++;
			CanChange = false;
		}
	}
}

void AMelodyCharacter::Move(const FInputActionValue& MoveValue)
{
	//TODO: make max speed based on stamina
	FVector2D MoveVector = MoveValue.Get<FVector2D>();

	if (Controller != nullptr)
	{
		if (MoveVector.X != 0)
		{
			AMelodyCharacter::LaneChange(MoveVector.X);
		}
	}
}

void AMelodyCharacter::Jump()
{
	if (GetCharacterMovement()->IsFalling()) return;
	if (!bJumpAffectsStamina || UseStamina(JumpStaminaCost))
	{
		ACharacter::Jump();
	}
}


void AMelodyCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp) 
	{
		if (AToken* Token = Cast<AToken>(OtherActor))
		{
			UE_LOG(LogTemp, Log, TEXT("OverlapDFASDF detected with %s"), *OtherActor->GetName());

			Token->Interact(this);
			Token->Destroy();
		}
        
	}
} 