#include "DisharmonyToken.h"
#include "MelodyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

void ADisharmonyToken::Interact(AMelodyCharacter* Character)
{
	if (Character)
	{
		Character->UseStamina(FMath::RandRange(10, 20));
		FTimerHandle SlowEffect;
		Character->GetWorld()->GetTimerManager().SetTimer(SlowEffect, [Character]() {
			Character->Speed = Character->RegSpeed;
		}, 3.0f, false);
	}
}
