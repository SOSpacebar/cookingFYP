// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "SpawnVolume.generated.h"


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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// My Spawn Object
	UPROPERTY(EditAnywhere, Category = "Spawner")
	TSubclassOf<class AAIDrone> spawnObject;

	FTimerHandle spawnTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float spawnDelayMinRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float spawnDelayMaxRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	uint8 spawnAmount;
};
