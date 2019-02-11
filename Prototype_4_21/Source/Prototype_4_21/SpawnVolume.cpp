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

	checkEnemyList = false;

	easyRate = 0;
	intRate = 0;
	hardRate = 0;
}

void ASpawnVolume::SpawnGameObject()
{
	if (spawnObject.Num() > 0)
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

			int32 randomNum = FMath::RandRange(0, 10);
			AAIDrone* drone;
			//Prespawning Drone for dynamical settings
			if (randomNum <= easyRate)
			{
				drone = world->SpawnActorDeferred<AAIDrone>(spawnObject[0], spawnTransform, this, Instigator);
			}
			else if (randomNum > intRate && randomNum < hardRate)
			{
				drone = world->SpawnActorDeferred<AAIDrone>(spawnObject[1], spawnTransform, this, Instigator);
			}
			else
			{
				drone = world->SpawnActorDeferred<AAIDrone>(spawnObject[2], spawnTransform, this, Instigator);
			}

			if (drone)
			{
				enemiesList.Add(drone);

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

				drone->isDead = false;
				//Tell the engine to spawn
				drone->FinishSpawning(spawnTransform);
			}

			// TODO SET AMOUNT SPAWN.
			if (spawnAmount > 1)
			{
				spawnAmount--;
				GetWorldTimerManager().SetTimer(spawnTimer, this, &ASpawnVolume::SpawnGameObject, spawnDelay, false);
			}
			else
			{
				checkEnemyList = true;
			}

		}
	}
}

void ASpawnVolume::SpawnBoss()
{
	if (spawnObject.Num() > 0)
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

			//Prespawning Drone for dynamical settings
			AAIDrone* const drone = world->SpawnActorDeferred<AAIDrone>(spawnObject[spawnObject.Num()-1], spawnTransform, this, Instigator);
			enemiesList.Add(drone);

			if (drone)
			{
				drone->isDead = false;
				//Tell the engine to spawn
				drone->FinishSpawning(spawnTransform);
			}

			// TODO SET AMOUNT SPAWN.
			if (spawnAmount > 1)
			{
				spawnAmount--;
				GetWorldTimerManager().SetTimer(spawnTimer, this, &ASpawnVolume::SpawnGameObject, spawnDelay, false);
			}
			else
			{
				checkEnemyList = true;
			}

		}
	}
}

void ASpawnVolume::DestoryAll()
{
	if (enemiesList.Num() > 0)
	{
		for (size_t i = 0; i < enemiesList.Num() - 1; i++)
		{
			enemiesList[i]->Destroy();
		}
	}

	enemiesList.Empty();
}

void ASpawnVolume::HandleSpawnEvents(uint8 _event)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Current Scenario, %d"), (uint8)gameManager->GetCurrScenario()));

	if (gameManager->GetCurrScenario() == EScenario::E_EVENT2)
	{
		spawnAmount = 3;
		spawnSide = ESpawnSide::E_LEFT;
		easyRate = 5;
		intRate = 6;
		hardRate = 9;
		SpawnGameObject();
	}

	else if (gameManager->GetCurrScenario() == EScenario::E_EVENT5)
	{
		spawnAmount = 3;
		spawnSide = ESpawnSide::E_RIGHT;
		easyRate = 9;
		intRate = 6;
		hardRate = 2;
		SpawnGameObject();
	}

	else if (gameManager->GetCurrScenario() == EScenario::E_EVENT7)
	{
		spawnAmount = 1;
		SpawnBoss();
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

	if (checkEnemyList)
	{
		if (enemiesList.Num() > 0)
		{
			for (size_t i = 0; i < enemiesList.Num(); i++)
			{
				if (!enemiesList[i]->isDead) //CHECK IS DRONE ALIVE
				{
					break;
				}
				else if (i == enemiesList.Num() - 1)
				{
					// ALL ENEMY DEAD
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("ALL DEAD")));
					uint8 currentScenario = (uint8)(gameManager->GetCurrScenario());
					checkEnemyList = false;
					currentScenario++;
					gameManager->SetCurrScenario((EScenario)currentScenario);
					gameManager->onScenarioComplete.Broadcast((uint8)gameManager->GetCurrScenario());
					enemiesList.Empty();
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("After Scenario, %d"), (uint8)gameManager->GetCurrScenario()));
				}
			}
		}
	}
}

FVector ASpawnVolume::GetRandomPointInVolume()
{
	FVector spawnOrigin = spawningBox->Bounds.Origin;
	FVector spawnExtent = spawningBox->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(spawnOrigin, spawnExtent);
}

