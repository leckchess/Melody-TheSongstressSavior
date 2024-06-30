#include "Token.h"

AToken::AToken()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AToken::BeginPlay()
{
	Super::BeginPlay();
}

void AToken::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AToken::Interact(AMelodyCharacter* Character)
{
	// Default interact implementation, can be overridden by derived classes
}
