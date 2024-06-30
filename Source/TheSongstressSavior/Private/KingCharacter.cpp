// Fill out your copyright notice in the Description page of Project Settings.

#include "KingCharacter.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

AKingCharacter::AKingCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//JumpTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
}

void AKingCharacter::BeginPlay()
{
	Super::BeginPlay();
	Melody = Cast<AMelodyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Melody != nullptr)
	{
		LaneSize = Melody->LaneSize;
		LaneChangeSpeed = Melody->LaneChangeSpeed;
		Speed = Melody->Speed;
	}
}

void AKingCharacter::Tick(float DeltaTime)
{
	if (Melody == nullptr || Melody->AutoForward == false)
	{
		return;
	}

	// TODO: Make dynamic to allow speeding up or slowing down
	FVector CurVec = GetActorLocation();
	SetActorLocation(CurVec + FVector(Speed, 0, 0));

	if (AKingCharacter::CheckLane(0) && CanChange)
	{
		AKingCharacter::PickLane();
	}

	if (RandomChangeChance != 0)
	{
		AKingCharacter::RandomSwitch(DeltaTime);
	}
	LaneInterp(DeltaTime);
}

void AKingCharacter::RandomSwitch(float DeltaTime)
{
	SwitchDelta = SwitchDelta + (1 * DeltaTime);

	if (SwitchDelta > 1)
	{
		SwitchDelta = 0;
		if (rand() % 100 < RandomChangeChance)
		{
			AKingCharacter::PickLane();
		}
	}
}

void AKingCharacter::PickLane()
{
	int MoveCount = 0;
	do { MoveCount = rand() % LaneCount + 1; } while (MoveCount == LanePos);

	MoveCount = MoveCount - LanePos;
	if (!AKingCharacter::CheckLane(MoveCount))
	{
		AKingCharacter::LaneChange(MoveCount);
	}
}

bool AKingCharacter::CheckLane(int Lane) const
{
	FHitResult HitResult;
	FVector BegTrace = GetActorLocation() + FVector(-400, LaneSize * Lane, 0);
	FVector EndTrace = BegTrace + FVector(SenseDistance + 400, 0, 0);
	FCollisionShape Sphere = FCollisionShape::MakeSphere(30);
	//DrawDebugLine(GetWorld(), BegTrace, EndTrace, FColor::Red);
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