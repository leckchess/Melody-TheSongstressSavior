#include "WinCollider.h"

AWinCollider::AWinCollider()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AWinCollider::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWinCollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWinCollider::Win(AMelodyCharacter* Melody)
{
	Melody->WonLevel = true;
	Melody->OnWinLevel();
}
