// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaController.h"

void UStaminaController::Initialize(float stamina)
{
	MaxStamina = stamina;
	CurrentStamina = stamina;
}

void UStaminaController::AddStaminaPercentage(float stamina)
{
	if (stamina <= 0)return;
	CurrentStamina = FMath::Clamp(stamina * MaxStamina + CurrentStamina, 0, MaxStamina);
}

UStaminaController::UStaminaController() : MaxStamina(100), CurrentStamina(100)
{
}

bool UStaminaController::UseStamina(float stamina)
{
	if (CurrentStamina - stamina < 0) return false;
	CurrentStamina -= stamina;
	return true;
}