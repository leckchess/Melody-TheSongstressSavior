#pragma once

#include "CoreMinimal.h"
#include "MelodyCharacter.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Token.generated.h"

class AMelodyCharacter;

UCLASS()
class THESONGSTRESSSAVIOR_API AToken : public AActor
{
	GENERATED_BODY()

public:
	AToken();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AMelodyCharacter* Character);
};
