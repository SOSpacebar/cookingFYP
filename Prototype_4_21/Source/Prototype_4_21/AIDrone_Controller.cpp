// Fill out your copyright notice in the Description page of Project Settings.

#include "AIDrone_Controller.h"
#include "AIDrone.h"
#include "AI_PathPoint.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

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

	if (aiCon)
	{
		if (aiCon->behaviorTree->BlackboardAsset)
		{
			blackBoardComponenet->InitializeBlackboard(*(aiCon->behaviorTree->BlackboardAsset));
		}

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAI_PathPoint::StaticClass(), pathPoints);
		behaviorTreeComponenet->StartTree(*aiCon->behaviorTree);
	}
}