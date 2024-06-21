// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MelodyHUD.generated.h"

/**
 * 
 */
UCLASS()
class THESONGSTRESSSAVIOR_API UMelodyHUD : public UUserWidget
{
	GENERATED_BODY()


public:

	void InitHUD(ACharacter* InOwnerCharacter);

	UFUNCTION()
	void UpdateStamina(float Amount, float CurrentStamina, float MaxStamina);

	void UpdateSpeed(float CurrentSpeed, float MaxSpeed);

	void ShowNoticication(FString Message);
	
	UFUNCTION(BlueprintImplementableEvent)
	void PlayNotificationAnimation(bool Show);

private:
	void HideNotification();

	
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UVerticalBox* VB_Speed;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* PB_Speed;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UHorizontalBox* HB_Stamina;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* PB_Stamina;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TB_Notifications;

	UPROPERTY(EditAnywhere)
	float NotificationTime = 1.f;

private:
	ACharacter* OwnerCharacter;

	FTimerHandle NotificationTimer;
};
