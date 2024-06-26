#pragma once

#include "CoreMinimal.h"
#include "Token.h"
#include "SpeedToken.generated.h"

UCLASS()
class THESONGSTRESSSAVIOR_API ASpeedToken : public AToken
{
	GENERATED_BODY()

public:
	virtual void Interact(AMelodyCharacter* Character) override;
};
