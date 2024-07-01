#pragma once

#include "CoreMinimal.h"
#include "Token.h"
#include "GameFramework/Actor.h"
#include "ObstaclesHandler.generated.h"

UCLASS()
class THESONGSTRESSSAVIOR_API AObstaclesHandler : public AActor
{
	GENERATED_BODY()
	
public:
	AObstaclesHandler();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	class AMelodyCharacter* Melody;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AToken>> Tokens;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ObstacleActor;

	// Obstacles will generate up to this distance
	UPROPERTY(EditAnywhere)
	int ObstaclesEnd = 20000;

	// Percent out of 100
	UPROPERTY(EditAnywhere)
	int LaneChangeChance = 80;

	// Percent out of 100
	UPROPERTY(EditAnywhere)
	int ObstacleChance = 25;

	// Percent out of 100
	UPROPERTY(EditAnywhere)
	int StaminaChance = 15;

	// Percent out of 100
	UPROPERTY(EditAnywhere)
	int DisharmonyChance = 10;

	// Percent out of 100
	UPROPERTY(EditAnywhere)
	int SpeedChance = 3;

	// Percent out of 100
	UPROPERTY(EditAnywhere)
	int ImmunityChance = 3;

	// Percent out of 100
	UPROPERTY(EditAnywhere)
	int JazzChance = 1;

	// Percent out of 100
	UPROPERTY(EditAnywhere)
	int MetalChance = 1;

	int DelayUntilSpecial = 5;
	int GetLaneCount = 2;
	int GetLanePos = 1;
	float GetLaneSize = 200.0;

	FActorSpawnParameters ObstacleParams;

	FVector InitialVector = FVector(0, 0, 0);
	FVector PlaceVector = FVector(0, 0, 0);
	FVector ObjectGap = FVector(1200, 0, 0);

};
