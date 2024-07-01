#include "SpeedToken.h"
#include "MelodyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

void ASpeedToken::Interact(AMelodyCharacter* Character)
{
	if (Character)
	{
		Character->Speed = Character->UpdateSpeed(10);

		// Reset after 3 seconds
		FTimerHandle TimerHandle;
		Character->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [Character]() {
			Character->Speed = Character->UpdateSpeed(-10);
			// Remove speed boost visual indicator here
		}, 3.0f, false);
	}
}
