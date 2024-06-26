#pragma once

#include "CoreMinimal.h"
#include "Token.h"
#include "JazzUltimateToken.generated.h"

UCLASS()
class THESONGSTRESSSAVIOR_API AJazzUltimateToken : public AToken
{
	GENERATED_BODY()

public:
	virtual void Interact(AMelodyCharacter* Character) override;
};
