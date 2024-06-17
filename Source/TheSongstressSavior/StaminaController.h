// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StaminaController.generated.h"

/**
 * 
 */
UCLASS()
class THESONGSTRESSSAVIOR_API UStaminaController : public UObject
{
	GENERATED_BODY()

private:
	float MaxStamina;
	float CurrentStamina;
	
public:
	void Initialize(float stamina);
	bool UseStamina(float stamina);
	float GetStamina() const;
	void AddStaminaPercentage(float stamina);

	UStaminaController();
};
