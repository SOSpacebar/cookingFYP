// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Environment.generated.h"

UCLASS(abstract)
 class PROTOTYPE_4_21_API AEnvironment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnvironment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Name of the Environment Object/Actor.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetName(FString _name);
};