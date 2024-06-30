#include "DisharmonyToken.h"
#include "MelodyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

void ADisharmonyToken::Interact(AMelodyCharacter* Character)
{
	if (Character)
	{
		Character->UseStamina(FMath::RandRange(0.0, 0.3));
	}
}
