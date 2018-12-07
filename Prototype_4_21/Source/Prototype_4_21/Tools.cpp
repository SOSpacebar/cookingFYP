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
	staticMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	//UE_LOG(LogTemp, Warning, TEXT("MyCharacter's Bool is %s"), (staticMesh->IsAnySimulatingPhysics() ? TEXT("True") : TEXT("False")));
}

void ATools::BeginPlay()
{
	Super::BeginPlay();
}

void ATools::Pickup_Implementation(USceneComponent* _attachTo)
{
	staticMesh->SetSimulatePhysics(false);

	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::KeepWorld, false);
	GetRootComponent()->AttachToComponent(_attachTo, AttachmentTransformRules);
}

void ATools::Drop_Implementation()
{
	staticMesh->SetSimulatePhysics(true);

	FDetachmentTransformRules DetatchmentTransformRules(EDetachmentRule::KeepWorld, true);
	DetachFromActor(DetatchmentTransformRules);
}

void ATools::Interact_Implementation()
{

}
