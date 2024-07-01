#include "JazzUltimateToken.h"
#include "MelodyCharacter.h"

void AJazzUltimateToken::Interact(AMelodyCharacter* Character)
{
	if (Character)
	{
		Character->ActivateMusicalMood(Mood::Jazz);
		Character->JazzActive = true;

		FTimerHandle JazzToken;
		Character->GetWorld()->GetTimerManager().SetTimer(JazzToken, [Character]() {
			Character->ActivateMusicalMood(Mood::Country);
			Character->JazzActive = false;
		}, 15.0f, false);
		// Character->SetRideAboveObstacles(true);
	}
}
