// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "SpawnVolume.generated.h"

UENUM(BlueprintType)
enum class ESpawnSide : uint8
{
	E_LEFT,
	E_RIGHT,
	E_BOTH,
	E_NONE
};

UCLASS()
class PROTOTYPE_4_21_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UBoxComponent* GetSpawnBox() const { return spawningBox; };

	UFUNCTION(BlueprintPure, Category = "Spawner")
	FVector GetRandomPointInVolume();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner", meta = (AllowPrivateAccess = "True"))
	UBoxComponent* spawningBox;

	float spawnDelay;

	void SpawnGameObject();
	void SpawnBoss();

	void DestoryAll();

	UFUNCTION(Category = "Spawner")
	void HandleSpawnEvents(uint8 _event);

	// My Spawn Object
	UPROPERTY(EditAnywhere, Category = "Spawner", meta = (AllowPrivateAccess = "True"))
		TArray<TSubclassOf<class AAIDrone>> spawnObject;
	
	// My enemy list Object
	UPROPERTY(EditAnywhere, Category = "Spawner", meta = (AllowPrivateAccess = "True"))
		TArray<class AAIDrone*> enemiesList;

	uint8 easyRate;
	uint8 intRate;
	uint8 hardRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle spawnTimer;

	class AGameManager *gameManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float spawnDelayMinRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float spawnDelayMaxRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	uint8 spawnAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	ESpawnSide spawnSide;


	bool checkEnemyList;
};
