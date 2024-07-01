#pragma once

#include "CoreMinimal.h"
#include "MelodyCharacter.h"
#include "GameFramework/Actor.h"
#include "WinCollider.generated.h"

UCLASS()
class THESONGSTRESSSAVIOR_API AWinCollider : public AActor
{
	GENERATED_BODY()
	
public:	
	AWinCollider();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Win(class AMelodyCharacter* Melody);

};
