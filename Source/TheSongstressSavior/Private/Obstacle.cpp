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
		const auto selectedIndex = FMath::RandRange(0, Meshes.Num() - 1);
		MeshComponent->SetStaticMesh(Meshes[selectedIndex]);
		MeshComponent->SetWorldScale3D(FVector(ObstacleScalar, ObstacleScalar, ObstacleScalar));
	}
	// Changed to Overlap from Mesh to account for size difference
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnComponentBeginOverlap);
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
