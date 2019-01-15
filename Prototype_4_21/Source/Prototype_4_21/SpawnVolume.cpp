// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnVolume.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "AIDrone.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	spawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = spawningBox;

	spawnDelayMinRange = 1.f;
	spawnDelayMaxRange = 3.f;
}

void ASpawnVolume::SpawnGameObject()
{
	if (spawnObject != NULL)
	{
		UWorld* const world = GetWorld();

		if (world)
		{
			// Setting spawn parameters
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = Instigator;

			// Get random location for spawn
			FVector spawnLocation = GetRandomPointInVolume();

			FRotator spawnRotation;
			spawnRotation.Yaw = 0;
			spawnRotation.Pitch = 0;
			spawnRotation.Roll = 0;


			FTransform spawnTransform;
			spawnTransform = FTransform(spawnRotation, spawnLocation);

			//AAIDrone* const drone = world->SpawnActor<AAIDrone>(spawnObject, spawnLocation, spawnRotation, spawnParams);

			//Prespawning Drone for dynamical settings
			AAIDrone* const drone = world->SpawnActorDeferred<AAIDrone>(spawnObject, spawnTransform, this, Instigator);
			
			if (drone)
			{
				//Set the details
				drone->SetSpawnSide(true);

				//Tell the engine to spawn
				UGameplayStatics::FinishSpawningActor(drone, spawnTransform);
				drone->FinishSpawning(spawnTransform);
			}


			// TODO SET AMOUNT SPAWN.
			GetWorldTimerManager().SetTimer(spawnTimer, this, &ASpawnVolume::SpawnGameObject, spawnDelay, false);
		}
	}
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
	spawnDelay = FMath::FRandRange(spawnDelayMinRange, spawnDelayMaxRange);
	GetWorldTimerManager().SetTimer(spawnTimer, this, &ASpawnVolume::SpawnGameObject, spawnDelay, false);
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetRandomPointInVolume()
{
	FVector spawnOrigin = spawningBox->Bounds.Origin;
	FVector spawnExtent = spawningBox->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(spawnOrigin, spawnExtent);
}

