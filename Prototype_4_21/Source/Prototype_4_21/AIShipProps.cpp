// Fill out your copyright notice in the Description page of Project Settings.

#include "AIShipProps.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AAIShipProps::AAIShipProps()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//nextLocation = "NextLocation";
}

// Called when the game starts or when spawned
void AAIShipProps::BeginPlay()
{
	Super::BeginPlay();

	//if (behaviorTree->BlackboardAsset)
	//{
	//	blackBoardComponenet->InitializeBlackboard(*(behaviorTree->BlackboardAsset));
	//	behaviorTreeComponenet->StartTree(*behaviorTree);
	//}
}

// Called every frame
void AAIShipProps::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

