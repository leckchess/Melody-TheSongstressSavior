#include "ImmunityToken.h"
#include "MelodyCharacter.h"
#include "TimerManager.h"

void AImmunityToken::Interact(AMelodyCharacter* Character)
{
	if (Character)
	{
		Character->IsInvulnerable = true;

		FTimerHandle InvulnerableTimer;
		Character->GetWorld()->GetTimerManager().SetTimer(InvulnerableTimer, [Character]() {
			Character->IsInvulnerable = false;
		}, 10.0f, false);
	}
}
