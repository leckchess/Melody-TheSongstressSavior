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
	
public:
	UStaminaController();

	void Initialize(float stamina);

	bool UseStamina(float stamina);

	float GetCurrentStamina() const { return CurrentStamina; }
	float GetMaxStamina() const { return MaxStamina; }
	
	void AddStaminaPercentage(float stamina);

private:
	float MaxStamina;
	float CurrentStamina;


};
