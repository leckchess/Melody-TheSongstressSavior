#pragma once

#include "CoreMinimal.h"
#include "Token.h"
#include "ImmunityToken.generated.h"

UCLASS()
class THESONGSTRESSSAVIOR_API AImmunityToken : public AToken
{
	GENERATED_BODY()

public:
	virtual void Interact(AMelodyCharacter* Character) override;
};
