// Fill out your copyright notice in the Description page of Project Settings.


#include "MelodyCharacter.h"

// Sets default values
AMelodyCharacter::AMelodyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMelodyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMelodyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMelodyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

