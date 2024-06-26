#include "SpeedToken.h"
#include "MelodyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

void ASpeedToken::Interact(AMelodyCharacter* Character)
{
	if (Character)
	{
		// Change the speed here
		Character->Speed = 50.0f;
		// Display speed boost visual indicator here
		// Example logging in BeginPlay
		UE_LOG(LogTemp, Log, TEXT("Characterss %s initialized."), *GetName());

		// FTimerHandle TimerHandle;
		// Character->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [Character]() {
		// 	Character->GetCharacterMovement()->MaxWalkSpeed /= 1.5f;
		// 	// Remove speed boost visual indicator here
		// }, 15.0f, false);
	}
}
