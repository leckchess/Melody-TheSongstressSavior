// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

#include "MelodyCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
AObstacle::AObstacle()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent());

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	if (Meshes.Num() > 0)
	{
		const auto selectedIndex = FMath::RandRange(0, Meshes.Num());
		MeshComponent->SetStaticMesh(Meshes[selectedIndex]);
	}
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnComponentBeginOverlap);
}

void AObstacle::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const auto character = Cast<AMelodyCharacter>(OtherActor);
	if(character!= nullptr)
	{
		character->UseStamina(StaminaLossOnHit);
		Destroy();
	}
}
