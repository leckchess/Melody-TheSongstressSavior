#include "DisharmonyToken.h"
#include "MelodyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

void ADisharmonyToken::Interact(AMelodyCharacter* Character)
{
	if (Character)
	{

		// Add logic for disharmony

		
		// Character->AddStamina(-Character->GetMaxStamina() * 0.15f);
		// Character->GetCharacterMovement()->MaxWalkSpeed *= 0.85f;
		// // Display negative effect visual indicator here
		//
		// FTimerHandle TimerHandle;
		// Character->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [Character]() {
		// 	Character->GetCharacterMovement()->MaxWalkSpeed /= 0.85f;
		// 	// Remove negative effect visual indicator here
		// }, 10.0f, false);
	}
}
