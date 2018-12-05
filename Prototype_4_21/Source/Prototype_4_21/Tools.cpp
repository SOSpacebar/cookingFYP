// Fill out your copyright notice in the Description page of Project Settings.

#include "Tools.h"
#include "Components/StaticMeshComponent.h"

ATools::ATools()
{
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = staticMesh;
	staticMesh->SetNotifyRigidBodyCollision(true);
	staticMesh->SetGenerateOverlapEvents(true);
	staticMesh->SetSimulatePhysics(true);

	//UE_LOG(LogTemp, Warning, TEXT("MyCharacter's Bool is %s"), (staticMesh->IsAnySimulatingPhysics() ? TEXT("True") : TEXT("False")));
}