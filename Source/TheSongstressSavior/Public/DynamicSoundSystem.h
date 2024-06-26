// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicSoundSystem.generated.h"

class USoundData;

UENUM(BlueprintType)
enum class SFX : uint8 {
	Jump       UMETA(DisplayName="Jump"),
	Collect    UMETA(DisplayName="Collect")
};

UENUM(BlueprintType)
enum class Mood : uint8 {
	Metal       UMETA(DisplayName="Metal"),
	Jazz        UMETA(DisplayName="Jazz"),
	Country     UMETA(DisplayName="Country")
};

UCLASS()
class THESONGSTRESSSAVIOR_API ADynamicSoundSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADynamicSoundSystem();
	UPROPERTY(EditAnywhere)
	TArray<USoundData*> SoundsData;

	UPROPERTY(VisibleAnywhere)
	UAudioComponent* SfxAudioComponent;

	UPROPERTY(VisibleAnywhere)
	UAudioComponent* MusicAudioComponent1;

	UPROPERTY(VisibleAnywhere)
	UAudioComponent* MusicAudioComponent2;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	float SwitchingMusicTime = 2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void PlaySound(SFX sfx) const;

	UFUNCTION()
	void SwitchMood(Mood mood);

	UFUNCTION()
	void SwitchMusic();

private:
	FTimerHandle SwitchMusicTimer;
	USoundData* CurrentSound;
	float Alpha;
};
