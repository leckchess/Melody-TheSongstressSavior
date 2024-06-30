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
		GetLanePos = (GetLanePos + 1) / 2;
		GetLaneCount = Melody->LaneCount;
		GetLaneSize = Melody->LaneSize;
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
		UClass* InActor = Tokens[0];
		int MoveCount;
		PlaceVector = PlaceVector + ObjectGap;

		if (rand() % 100 < LaneChangeChance)
		{
			do { MoveCount = rand() % GetLaneCount + 1; } while ( MoveCount == GetLanePos );
			MoveCount = MoveCount - GetLanePos;
			GetLanePos = GetLanePos + MoveCount;
			PlaceVector = PlaceVector + FVector(0, MoveCount * GetLaneSize, 0);
		}
		if (rand() % 100 < 25)
		{
			InActor = ObstacleActor;
		}
		
		GetWorld()->SpawnActor<AActor>(
			InActor,
			PlaceVector,
			FRotator(0, 0, 0),
			ObstacleParams
		);
	}
}

