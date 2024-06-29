#include "ObstaclesHandler.h"
#include "MelodyCharacter.h"
#include "Kismet/GameplayStatics.h"

AObstaclesHandler::AObstaclesHandler()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AObstaclesHandler::BeginPlay()
{
	Super::BeginPlay();
	Melody = Cast<AMelodyCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	// Initialize Obstacles
	InitialVector = GetActorLocation();
	ObjectGap = FVector(Melody->Speed * 80, 0, 0);
	PlaceVector = InitialVector + FVector(3 * ObjectGap.X, 0, 0);
}

void AObstaclesHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get start position
	// Move forward by set default gap

}

