// Fill out your copyright notice in the Description page of Project Settings.

#include "AIDrone_Controller.h"
#include "AIDrone.h"
#include "AI_RightPathPoint.h"
#include "AI_LeftPathPoint.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SpawnVolume.h"

AAIDrone_Controller::AAIDrone_Controller()
{
	// Initialize Blackboard and BehaviourTree Components
	behaviorTreeComponenet = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourComp"));
	blackBoardComponenet = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));

	// Initialize Blackboard Keys
	player = "Target";
	nextLocation = "NextLocation";

	currentPoint = 0;
}

void AAIDrone_Controller::SetPlayerCoord(APawn* _pawn)
{
	if (blackBoardComponenet)
	{
		blackBoardComponenet->SetValueAsObject(player, _pawn);
	}
}

void AAIDrone_Controller::Possess(APawn *_pawn)
{
	Super::Possess(_pawn);

	// Reference To Character
	AAIDrone* aiCon = Cast<AAIDrone>(_pawn);

	//Set Random Movement Speed
	float randomSpeed = FMath::FRandRange(6000, 15000);
	GetCharacter()->GetCharacterMovement()->MaxFlySpeed = randomSpeed;

	if (aiCon)
	{
		if (aiCon->behaviorTree->BlackboardAsset)
		{
			blackBoardComponenet->InitializeBlackboard(*(aiCon->behaviorTree->BlackboardAsset));
		}

		uint8 randomSide = FMath::RandRange(0, 1);

		switch (aiCon->GetSpawnSide())
		{
		case ESpawnSide::E_LEFT:
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAI_LeftPathPoint::StaticClass(), pathPoints);
			break;
		case ESpawnSide::E_RIGHT:
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAI_RightPathPoint::StaticClass(), pathPoints);
			break;
		case ESpawnSide::E_BOTH:
			if (randomSide == 0)
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAI_LeftPathPoint::StaticClass(), pathPoints);
			else
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAI_RightPathPoint::StaticClass(), pathPoints);
			break;
		case ESpawnSide::E_NONE:
			break;
		default:
			break;
		}

		if (pathPoints.Num() <= 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("No Paths Assigned")));
		}

		behaviorTreeComponenet->StartTree(*aiCon->behaviorTree);
	}
}