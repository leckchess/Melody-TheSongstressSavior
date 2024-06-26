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
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	AMelodyCharacter* Melody;

	UPROPERTY(EditAnywhere, Category = "Enemy Controller")
	float SenseDistance = 800;

	UPROPERTY(EditAnywhere, Category = "Enemy Controller")
	float RandomChangeChance = 40;

	void RandomSwitch(float DeltaTime);
	void PickLane();
	bool CheckLane(int Lane) const;

	float SwitchDelta = 0.0;
};
