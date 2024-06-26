#pragma once

#include "CoreMinimal.h"
#include "Token.h"
#include "StaminaToken.generated.h"

UCLASS()
class THESONGSTRESSSAVIOR_API AStaminaToken : public AToken
{
	GENERATED_BODY()

public:
	virtual void Interact(AMelodyCharacter* Character) override;
};
