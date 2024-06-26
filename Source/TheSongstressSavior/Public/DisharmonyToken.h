#pragma once

#include "CoreMinimal.h"
#include "Token.h"
#include "DisharmonyToken.generated.h"

UCLASS()
class THESONGSTRESSSAVIOR_API ADisharmonyToken : public AToken
{
	GENERATED_BODY()

public:
	virtual void Interact(AMelodyCharacter* Character) override;
};
