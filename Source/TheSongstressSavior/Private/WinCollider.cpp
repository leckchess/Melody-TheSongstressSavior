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
	GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::Red, FString::Printf(TEXT("WINNER")));
}
