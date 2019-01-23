// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnVolume.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "AIDrone.h"
#include "GameManager.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	spawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = spawningBox;

	spawnDelayMinRange = 2.f;
	spawnDelayMaxRange = 4.f;
}

void ASpawnVolume::SpawnGameObject()
{
	if (spawnObject != NULL)
	{
		UWorld* const world = GetWorld();

		if (world)
		{
			// Setting spawn parameters
			//FActorSpawnParameters spawnParams;
			//spawnParams.Owner = this;
			//spawnParams.Instigator = Instigator;

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
				switch (spawnSide)
				{
				case ESpawnSide::E_LEFT:
					drone->SetSpawnSide(ESpawnSide::E_LEFT);
					break;
				case ESpawnSide::E_RIGHT:
					drone->SetSpawnSide(ESpawnSide::E_RIGHT);
					break;
				case ESpawnSide::E_BOTH:
					drone->SetSpawnSide(ESpawnSide::E_BOTH);
					break;
				case ESpawnSide::E_NONE:
					break;
				default:
					break;
				}

				//Tell the engine to spawn
				drone->FinishSpawning(spawnTransform);
			}

			// TODO SET AMOUNT SPAWN.
			if (spawnAmount > 0)
			{
				GetWorldTimerManager().SetTimer(spawnTimer, this, &ASpawnVolume::SpawnGameObject, spawnDelay, false);
				spawnAmount--;
			}

		}
	}
}

void ASpawnVolume::HandleSpawnEvents(uint8 _event)
{
	//SpawnGameObject();
	//gameManager->SetCurrScenario((EScenario)_event);
	if (gameManager->GetCurrScenario() == EScenario::E_EVENT1)
	{
		//gameManager->SetCurrScenario((EScenario)_event);
		spawnAmount = 25;
		spawnSide = ESpawnSide::E_BOTH;
		SpawnGameObject();
	}
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(spawnTimer, this, &ASpawnVolume::SpawnGameObject, spawnDelay, false);
	
	spawnDelay = FMath::FRandRange(spawnDelayMinRange, spawnDelayMaxRange);

	gameManager = (AGameManager*)GetWorld()->GetAuthGameMode();

	if (gameManager)
	{
		gameManager->onScenarioComplete.AddDynamic(this, &ASpawnVolume::HandleSpawnEvents);
	}
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

