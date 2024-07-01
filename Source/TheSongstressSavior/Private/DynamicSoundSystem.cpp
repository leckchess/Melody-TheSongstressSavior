// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicSoundSystem.h"
#include "Components/AudioComponent.h"
#include "SoundData.h"

// Sets default values
ADynamicSoundSystem::ADynamicSoundSystem()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SfxAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SfxAudioComponent"));
	SfxAudioComponent->SetupAttachment(GetRootComponent());

	AmbienceAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AmbienceAudioComponent"));
	AmbienceAudioComponent->SetupAttachment(GetRootComponent()); 
	
	HorseAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("HorseAudioComponent"));
	HorseAudioComponent->SetupAttachment(GetRootComponent());

	MusicAudioComponent1 = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicAudioComponent1"));
	MusicAudioComponent1->SetupAttachment(GetRootComponent());

	MusicAudioComponent2 = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicAudioComponent2"));
	MusicAudioComponent2->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ADynamicSoundSystem::BeginPlay()
{
	Super::BeginPlay();

	if (BGMusicData.Num() == 0) { return; }

	if(BGMusicData.Contains(Mood::Country))
	{
		MusicAudioComponent1->Sound = BGMusicData[Mood::Country];
		MusicAudioComponent1->Play();
	}
}

void ADynamicSoundSystem::OnGameStarted()
{
	AmbienceAudioComponent->Sound = MainSoundData->Ambience;
	HorseAudioComponent->Sound = MainSoundData->HorseSteps;

	AmbienceAudioComponent->Play();
	HorseAudioComponent->Play();
}

void ADynamicSoundSystem::PlaySound(SFX sfx) const
{
	switch (sfx)
	{
	case SFX::Collect:
		SfxAudioComponent->Sound = MainSoundData->Collect;
		break;
	case SFX::Notification:
		SfxAudioComponent->Sound = MainSoundData->Notification;
		break;
	default: ;
		break;
	}
	SfxAudioComponent->Play();
}

void ADynamicSoundSystem::SwitchMood(Mood mood)
{
	if (BGMusicData.Contains(mood) == false)
	{
		return;
	}

	CurrentMood = mood;
	MusicAudioComponent2->Stop();
	MusicAudioComponent2->Sound = BGMusicData[CurrentMood];
	MusicAudioComponent2->Play();

	MusicAudioComponent1->AdjustVolume(SwitchingMusicTime, 0.f);
	MusicAudioComponent2->AdjustVolume(SwitchingMusicTime, 1.f);
}

void ADynamicSoundSystem::SwitchMood(Mood mood1, Mood Mood2, float Percentage)
{
	if (CurrentMood != Mood::Country || BGMusicData.Contains(mood1) == false || BGMusicData.Contains(Mood2) == false)
	{
		return;
	}

	MusicAudioComponent1->Sound = BGMusicData[mood1];

	if (MusicAudioComponent2->Sound != BGMusicData[Mood2])
	{
		MusicAudioComponent2->Stop();
		MusicAudioComponent2->Sound = BGMusicData[Mood2];
	}

	if(MusicAudioComponent2->IsPlaying() == false)
	{
		MusicAudioComponent2->Play();
	}

	if (MusicAudioComponent1->IsPlaying() == false)
	{
		MusicAudioComponent1->Play();
	}

	MusicAudioComponent1->AdjustVolume(0.1f, Percentage);
	MusicAudioComponent2->AdjustVolume(0.1f, 1 - Percentage);
}
