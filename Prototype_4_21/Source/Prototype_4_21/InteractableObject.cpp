// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableObject.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	action = "Action";
	objectID = "ID NOT SET";

}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AInteractableObject::Pickup_Implementation(USceneComponent * _attachTo)
{
}

void AInteractableObject::Drop_Implementation()
{
}

void AInteractableObject::Interact_Implementation()
{
}

FString AInteractableObject::GetInteractableText() const
{
	return FString::Printf(TEXT("%s : Interact to %s."), *name, *action);
}
