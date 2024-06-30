#include "SpeedToken.h"
#include "MelodyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

void ASpeedToken::Interact(AMelodyCharacter* Character)
{
	if (Character)
	{
		// Change the speed here
		float curSpeed = Character->Speed;
		Character->Speed = curSpeed * 3;
		// Display speed boost visual indicator here
		// Example logging in BeginPlay
		UE_LOG(LogTemp, Log, TEXT("Characterss %s initialized."), *GetName());

		// Reset after 3 seconds
		FTimerHandle TimerHandle;
		Character->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [Character]() {
			Character->Speed = Character->Speed / 3;
			// Remove speed boost visual indicator here
		}, 3.0f, false);
	}
}
