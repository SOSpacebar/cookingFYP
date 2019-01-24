// Fill out your copyright notice in the Description page of Project Settings.

#include "SmallShipAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIShipProps.h"


ASmallShipAIController::ASmallShipAIController()
{
	// Initialize Blackboard and BehaviourTree Components
	behaviorTreeComponenet = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourComp"));
	blackBoardComponenet = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));

	// Initialize Blackboard Keys
	nextLocation = "NextLocation";

	currentPoint = 0;
}

void ASmallShipAIController::Possess(APawn *_pawn)
{
	Super::Possess(_pawn);

	// Reference To Character
	AAIShipProps* aiShip = Cast<AAIShipProps>(_pawn);

	if (aiShip)
	{
		if (aiShip->behaviorTree->BlackboardAsset)
		{
			blackBoardComponenet->InitializeBlackboard(*(aiShip->behaviorTree->BlackboardAsset));
		}

		pathPoints = aiShip->GetPathArray();
		behaviorTreeComponenet->StartTree(*aiShip->behaviorTree);
	}
}