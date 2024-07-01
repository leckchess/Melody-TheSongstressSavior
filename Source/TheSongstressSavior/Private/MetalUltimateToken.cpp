#include "MetalUltimateToken.h"
#include "MelodyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

void AMetalUltimateToken::Interact(AMelodyCharacter* Character)
{
	if (Character)
	{
		Character->ActivateMusicalMood(Mood::Metal);
		Character->MetalActive = true;
		Character->IsInvulnerable = true;
		Character->UpdateSpeed(12);

		FTimerHandle MetalToken;
		Character->GetWorld()->GetTimerManager().SetTimer(MetalToken, [Character]() {
			Character->ActivateMusicalMood(Mood::Country);
			Character->MetalActive = false;
			Character->IsInvulnerable = false;
			Character->UpdateSpeed(-12);
		}, 15.0f, false);
	}
}
