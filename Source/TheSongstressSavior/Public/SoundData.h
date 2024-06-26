// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SoundData.generated.h"

/**
 * 
 */

USTRUCT()
struct FSound
{
	GENERATED_BODY()
	
};

UCLASS()
class THESONGSTRESSSAVIOR_API USoundData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	USoundWave* Jump;

	UPROPERTY(EditAnywhere)
	USoundWave* Collect;

	UPROPERTY(EditAnywhere)
	USoundWave* BgMusic;
};
