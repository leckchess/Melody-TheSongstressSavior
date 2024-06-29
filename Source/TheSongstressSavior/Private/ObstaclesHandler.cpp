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

	if (Melody != nullptr)
	{
		ObjectGap = FVector(Melody->Speed * 80, 0, 0);
	}
	else
	{
		ObjectGap = FVector(1200, 0, 0);
	}
	InitialVector = GetActorLocation();
	PlaceVector = InitialVector + FVector(3 * ObjectGap.X, 0, 0);
	GetWorld()->SpawnActor<AActor>(Tokens[0], PlaceVector, FRotator(0, 0, 0), ObstacleParams);
}

void AObstaclesHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlaceVector.X < ObstaclesEnd)
	{
		PlaceVector = PlaceVector + ObjectGap;
		DrawDebugSphere(GetWorld(), PlaceVector, 40, 24, FColor::Blue, false, 10);
	}
}

