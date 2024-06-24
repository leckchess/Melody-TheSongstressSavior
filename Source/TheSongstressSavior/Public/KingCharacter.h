// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MelodyCharacter.h"
#include "KingCharacter.generated.h"

UCLASS()
class THESONGSTRESSSAVIOR_API AKingCharacter : public AMelodyCharacter
{
	GENERATED_BODY()

public:
	AKingCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Enemy Perception")
	float SenseDistance = 2000;

	bool CheckLane(int Lane);

public:
	virtual void Tick(float DeltaTime) override;
};
