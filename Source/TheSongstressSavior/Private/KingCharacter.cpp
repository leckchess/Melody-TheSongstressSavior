// Fill out your copyright notice in the Description page of Project Settings.

#include "KingCharacter.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

AKingCharacter::AKingCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AKingCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AKingCharacter::Tick(float DeltaTime)
{
	// TODO: Make dynamic to allow speeding up or slowing down
	FVector CurVec = GetActorLocation();
	SetActorLocation(CurVec + FVector(12, 0, 0));
	GEngine->AddOnScreenDebugMessage(0, DeltaTime, FColor::Red, FString::Printf(TEXT("Lane: %d"), LanePos));

	if (AKingCharacter::CheckLane(0) && CanChange)
	{
		int PickDirection = (rand() % 2 == 0) ? -1 : 1;
		if (AKingCharacter::CheckLane(PickDirection))
		{
			LaneChange(PickDirection);
		}
		else
		{
			LaneChange(-PickDirection);
		}
	}

	LaneInterp(DeltaTime);
}

bool AKingCharacter::CheckLane(int Lane)
{
	FHitResult HitResult;
	FVector BegTrace = GetActorLocation() + FVector(0, LaneSize * Lane, 0);
	FVector EndTrace = BegTrace + FVector(SenseDistance, 0, 0);
	FCollisionShape Sphere = FCollisionShape::MakeSphere(30);
	DrawDebugLine(GetWorld(), BegTrace, EndTrace, FColor::Red);
	bool GetHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		BegTrace,
		EndTrace,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		Sphere
	);

	return GetHit;
}