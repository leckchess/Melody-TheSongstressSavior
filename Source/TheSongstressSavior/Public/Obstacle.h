// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

class UBoxComponent;
class UObstacleDisplayData;
UCLASS()
class THESONGSTRESSSAVIOR_API AObstacle : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float StaminaLossOnHit;
	UPROPERTY(EditAnywhere)
	float ObstacleScalar = 2;
	UPROPERTY(VisibleAnywhere)
    USceneComponent* Root;
	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditAnywhere)
	TArray<UStaticMesh*> Meshes;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;
	
	AObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
