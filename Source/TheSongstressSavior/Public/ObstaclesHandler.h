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
	int ObstaclesEnd = 20000;

	UPROPERTY(EditAnywhere)
	// Percent out of 100
	int LaneChangeChance = 50;

	int GetLaneCount = 2;
	int GetLanePos = 1;
	float GetLaneSize = 200.0;

	FActorSpawnParameters ObstacleParams;

	FVector InitialVector = FVector(0, 0, 0);
	FVector PlaceVector = FVector(0, 0, 0);
	FVector ObjectGap = FVector(1200, 0, 0);

};
