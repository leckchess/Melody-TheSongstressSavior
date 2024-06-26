#include "Token.h"
#include "MelodyCharacter.h"

AToken::AToken()
{
	PrimaryActorTick.bCanEverTick = true;

	// Optionally, set up a default mesh for the token
	// UStaticMeshComponent* Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TokenMesh"));
	// RootComponent = Mesh;
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
