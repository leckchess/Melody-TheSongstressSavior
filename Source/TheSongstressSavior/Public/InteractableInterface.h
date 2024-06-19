// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.generated.h"

UCLASS()
class THESONGSTRESSSAVIOR_API AInteractableInterface : public AActor
{
	GENERATED_BODY()

public:
	virtual void Interact() {};
	virtual void StopInteraction() {};

public:
	UPROPERTY(EditAnywhere, Category = "Token")
	bool bTimeBasedToken = false;

	UPROPERTY(EditAnywhere, Category = "Time Based Token", meta = (EditCondition = "bTimeBasedToken", EditConditionHides))
	float TokenTime = 0.5f;
};
