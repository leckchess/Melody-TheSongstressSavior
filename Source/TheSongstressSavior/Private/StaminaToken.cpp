#include "StaminaToken.h"
#include "MelodyCharacter.h"

void AStaminaToken::Interact(AMelodyCharacter* Character)
{
	if (Character)
	{
		UE_LOG(LogTemp, Log, TEXT("stamina token  %s initialized."), *GetName());

		 // Add Stamina logic
		//Character->AddStamina(MaxStamina * 0.25f);
	}
}
