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
		ObjectGap = FVector(Melody->Speed * 120, 0, 0);
		GetLanePos = (GetLanePos + 1) / 2;
		GetLaneCount = Melody->LaneCount;
		GetLaneSize = Melody->LaneSize;
	}
	InitialVector = GetActorLocation();
	PlaceVector = InitialVector + FVector(3 * ObjectGap.X, 0, 0);
	GetWorld()->SpawnActor<AActor>(Tokens[0], PlaceVector, FRotator(0, 0, 0), ObstacleParams);

	// Chance Percentage Calculation
	StaminaChance = StaminaChance + ObstacleChance;
	DisharmonyChance = DisharmonyChance + StaminaChance;
	SpeedChance = SpeedChance + DisharmonyChance;
	ImmunityChance = ImmunityChance + SpeedChance;
	JazzChance = JazzChance + ImmunityChance;
	MetalChance = MetalChance + JazzChance;
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
			GetWorld()->SpawnActor<AActor>(
				ObstacleActor,
				PlaceVector,
				FRotator(0, 0, 0),
				ObstacleParams
			);

			do { MoveCount = rand() % GetLaneCount + 1; } while ( MoveCount == GetLanePos );
			MoveCount = MoveCount - GetLanePos;
			GetLanePos = GetLanePos + MoveCount;
			PlaceVector = PlaceVector + FVector(0, MoveCount * GetLaneSize, 0);
		}

		// DO NOT change order of the Tokens in BP or in script
		// Change 'Chance' value instead
		int RandSelect = rand() % 100;
		if (Tokens.Num() >= 6)
		{
			if (RandSelect <= ObstacleChance)
			{
				InActor = ObstacleActor;
				GetWorld()->SpawnActor<AActor>(
					Tokens[0],
					PlaceVector + FVector(0, 0, 120),
					FRotator(0, 0, 0),
					ObstacleParams
				);
			}
			else if (RandSelect > ObstacleChance && RandSelect <= StaminaChance)
			{
				// Stamina Token
				InActor = Tokens[1];
			}
			else if (RandSelect > StaminaChance && RandSelect <= DisharmonyChance)
			{
				// Disharmony Token
				InActor = Tokens[2];
			}
			else if (RandSelect > DisharmonyChance && RandSelect <= SpeedChance)
			{
				// Speed Token
				InActor = Tokens[3];
			}
			else if (RandSelect > SpeedChance && RandSelect <= ImmunityChance)
			{
				// Immunity Token
				InActor = Tokens[4];
			}
			else if (RandSelect > ImmunityChance && RandSelect <= JazzChance)
			{
				// Jazz Token
				InActor = Tokens[5];
			}
			else if (RandSelect > JazzChance && RandSelect <= MetalChance)
			{
				// Metal Token
				InActor = Tokens[6];
			}
		}
		
		GetWorld()->SpawnActor<AActor>(
			InActor,
			PlaceVector,
			FRotator(0, 0, 0),
			ObstacleParams
		);
	}
}

