// Fill out your copyright notice in the Description page of Project Settings.


#include "MelodyHUD.h"
#include "MelodyCharacter.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

void UMelodyHUD::InitHUD(ACharacter* InOwnerCharacter)
{
	OwnerCharacter = InOwnerCharacter;

	if (OwnerCharacter == nullptr) { return; }

	if (AMelodyCharacter* Melody = Cast<AMelodyCharacter>(OwnerCharacter))
	{
		Melody->OnUseStamina.AddUObject(this, &UMelodyHUD::UpdateStamina);
	}

	if (PB_Speed)
	{
		PB_Speed->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (TB_Notifications)
	{
		TB_Notifications->SetVisibility(ESlateVisibility::Collapsed);
		ShowNoticication("HIII");
	}
}

void UMelodyHUD::UpdateStamina(float Amount, float CurrentStamina, float MaxStamina)
{
	if (PB_Stamina == nullptr) { return; }

	if (MaxStamina == 0)
	{
		PB_Stamina->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	float Percentage = CurrentStamina / MaxStamina;
	if (Percentage > 0.7f)
	{
		PB_Stamina->SetFillColorAndOpacity(FColor::Green);
	}
	else if (Percentage <= 0.7f && Percentage > 0.3f)
	{
		PB_Stamina->SetFillColorAndOpacity(FColor::Yellow);
	}
	else if (Percentage <= 0.3f)
	{
		PB_Stamina->SetFillColorAndOpacity(FColor::Red);
	}

	PB_Stamina->SetPercent(Percentage);
}

void UMelodyHUD::UpdateSpeed(float CurrentSpeed, float MaxSpeed)
{
	if (PB_Speed == nullptr) { return; }

	if (MaxSpeed == 0)
	{
		PB_Speed->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	float Percentage = CurrentSpeed / MaxSpeed;
	if (Percentage > 0.7f)
	{
		PB_Speed->SetFillColorAndOpacity(FColor::Red);
	}
	else if (Percentage <= 0.7f && Percentage > 0.3f)
	{
		PB_Speed->SetFillColorAndOpacity(FColor::Yellow);
	}
	else if (Percentage <= 0.3f)
	{
		PB_Speed->SetFillColorAndOpacity(FColor::Green);
	}

	PB_Speed->SetPercent(Percentage);
}

void UMelodyHUD::ShowNoticication(FString Message)
{
	if (TB_Notifications == nullptr) { return; }

	TB_Notifications->SetText(FText::FromString(Message));
	PlayNotificationAnimation(true);

	if (OwnerCharacter && OwnerCharacter->GetWorld())
	{
		if (OwnerCharacter->GetWorld()->GetTimerManager().IsTimerActive(NotificationTimer))
		{
			OwnerCharacter->GetWorld()->GetTimerManager().ClearTimer(NotificationTimer);
		}

		OwnerCharacter->GetWorld()->GetTimerManager().SetTimer(NotificationTimer, this, &UMelodyHUD::HideNotification, NotificationTime, false);
	}
}

void UMelodyHUD::HideNotification()
{
	PlayNotificationAnimation(false);
}
