#pragma once

#include "CoreMinimal.h"
#include "Token.h"
#include "MetalUltimateToken.generated.h"

UCLASS()
class THESONGSTRESSSAVIOR_API AMetalUltimateToken : public AToken
{
	GENERATED_BODY()

public:
	virtual void Interact(AMelodyCharacter* Character) override;
};
