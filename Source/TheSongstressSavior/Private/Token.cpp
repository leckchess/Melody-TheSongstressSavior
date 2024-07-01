#include "Token.h"

AToken::AToken()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AToken::BeginPlay()
{
	Super::BeginPlay();
}

void AToken::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AToken::Interact(AMelodyCharacter* Character)
{
	if (Character && Character->GetOwner()->GetName() != "AIController_0")
	{
		Character->Speed = Character->UpdateSpeed(2);
		Character->AddStamina(0.2);

		FTimerHandle TimerHandle;
		Character->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [Character]() {
			Character->Speed = Character->UpdateSpeed(-1);
		}, 1.0f, false);

		Character->OnCollectToken();
	}
}
