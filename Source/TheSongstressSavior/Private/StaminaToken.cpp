#include "StaminaToken.h"

void AStaminaToken::Interact(AMelodyCharacter* Character)
{
	if (Character)
	{
		Character->AddStamina(0.6);
	}
}
