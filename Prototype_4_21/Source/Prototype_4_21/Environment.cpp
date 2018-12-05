// Fill out your copyright notice in the Description page of Project Settings.

#include "Environment.h"

// Sets default values
AEnvironment::AEnvironment()
{
 	// Set this actor to not call Tick() every frame.  This is a base class this should not be true here.
	PrimaryActorTick.bCanEverTick = false;

	name = "NOTSET";
}

// Called when the game starts or when spawned
void AEnvironment::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnvironment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnvironment::SetName(FString _name)
{
	name = _name;
}

