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

	MusicAudioComponent1 = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicAudioComponent1"));
	MusicAudioComponent1->SetupAttachment(GetRootComponent());

	MusicAudioComponent2 = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicAudioComponent2"));
	MusicAudioComponent2->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ADynamicSoundSystem::BeginPlay()
{
	Super::BeginPlay();
	CurrentSound = SoundsData[0];

	MusicAudioComponent1->Sound = CurrentSound->BgMusic;
	MusicAudioComponent1->Play();
}

void ADynamicSoundSystem::PlaySound(SFX sfx) const
{
	switch (sfx)
	{
	case SFX::Collect:
		SfxAudioComponent->Sound = CurrentSound->Collect;
		break;
	case SFX::Jump:
		SfxAudioComponent->Sound = CurrentSound->Jump;
	default: ;
	}
	SfxAudioComponent->Play();
}

void ADynamicSoundSystem::SwitchMood(Mood mood)
{
	MusicAudioComponent2->Sound = CurrentSound->BgMusic;
	MusicAudioComponent2->VolumeMultiplier = 1;
	CurrentSound = SoundsData[static_cast<int>(mood)];
	MusicAudioComponent1->Sound = CurrentSound->BgMusic;
	MusicAudioComponent2->VolumeMultiplier = 0;

	MusicAudioComponent1->Play();
	MusicAudioComponent2->Play();

	GetWorld()->GetTimerManager().ClearTimer(SwitchMusicTimer);
	GetWorld()->GetTimerManager().SetTimer(SwitchMusicTimer, this, &ADynamicSoundSystem::SwitchMusic, 0.03, true);
}

void ADynamicSoundSystem::SwitchMusic()
{
	Alpha += SwitchingMusicTime / 0.03; //in 2 second
	if (Alpha >= 1)
	{
		Alpha = 0;
		MusicAudioComponent2->Stop();
		MusicAudioComponent1->VolumeMultiplier = 1;
		MusicAudioComponent2->VolumeMultiplier = 0;
		GetWorld()->GetTimerManager().ClearTimer(SwitchMusicTimer);
		return;
	}

	MusicAudioComponent1->VolumeMultiplier = Alpha;
	MusicAudioComponent2->VolumeMultiplier = 1 - Alpha;
}
