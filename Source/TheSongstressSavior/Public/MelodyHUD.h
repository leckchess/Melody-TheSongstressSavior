// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MelodyHUD.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnGameStarted)
DECLARE_MULTICAST_DELEGATE(FOnShowNotification)

UENUM(BlueprintType)
enum ENotificationType
{
	EMessage,
	EWarning,
	EError
};

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

	void ShowNoticication(FString Message, ENotificationType NotificationType);
	
	UFUNCTION(BlueprintImplementableEvent)
	void PlayNotificationAnimation(bool Show);

	void NotifyStaminaUpdate(float Percentage);

	void OnLevelEnds();
private:
	void HideNotification();

	UFUNCTION()
	void OnPlayButtonClicked();

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UOverlay* MainMenuOverlay;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* PlayButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UOverlay* InGameOverlay;

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

	FOnGameStarted OnGameStarted;
	FOnShowNotification OnShowNotification;

private:
	ACharacter* OwnerCharacter;

	FTimerHandle NotificationTimer;

	float PrevPercentage = 1;
};
