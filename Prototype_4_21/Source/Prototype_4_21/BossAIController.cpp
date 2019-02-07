// Fill out your copyright notice in the Description page of Project Settings.

#include "BossAIController.h"
#include "AIDrone.h"
#include "AIBoss_PathPoint.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


void ABossAIController::Possess(APawn *_pawn)
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

		TArray<AActor*> tempholder;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIBoss_PathPoint::StaticClass(), tempholder);
		pathPoints.SetNum(4);

		for (size_t i = 0; i < tempholder.Num(); i++)
		{
			AAIBoss_PathPoint* point = Cast<AAIBoss_PathPoint>(tempholder[i]);
			pathPoints[point->direction] = point;
		}

		if (pathPoints.Num() <= 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Boss No Paths Assigned")));
		}

		behaviorTreeComponenet->StartTree(*aiCon->behaviorTree);
	}
}