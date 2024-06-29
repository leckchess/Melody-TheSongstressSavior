#pragma once

#include "CoreMinimal.h"
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
	TSubclassOf<class AStaminaToken> StaminaToken;

	FVector InitialVector = FVector(0, 0, 0);
	FVector PlaceVector = FVector(0, 0, 0);
	FVector ObjectGap = FVector(0, 0, 0);

};
