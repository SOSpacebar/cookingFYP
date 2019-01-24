// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_SelectNextPoint.h"
#include "AI_PathPoint.h"
#include "SmallShipAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBT_SelectNextPoint::ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory)
{
	ASmallShipAIController* aiCon = Cast<ASmallShipAIController>(_ownerComp.GetAIOwner());

	if (aiCon)
	{
		// Get BB component
		UBlackboardComponent* blackBoardComp = aiCon->GetBlackboardComponent();

		AAI_PathPoint* currentPoint = Cast<AAI_PathPoint>(blackBoardComp->GetValueAsObject("NextLocation"));

		TArray<AActor*> availablePathPoints = aiCon->GetPathArray();

		AAI_PathPoint* nextPoint = nullptr;

		if (availablePathPoints.Num() == 0) // Return if no paths.
		{
			return EBTNodeResult::Aborted;
		}

		if (aiCon->currentPoint != availablePathPoints.Num() - 1)
		{
			nextPoint = Cast<AAI_PathPoint>(availablePathPoints[++aiCon->currentPoint]);
		}
		else
		{
			nextPoint = Cast<AAI_PathPoint>(availablePathPoints[0]);
			aiCon->currentPoint = 0;
		}

		blackBoardComp->SetValueAsObject("NextLocation", nextPoint);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
