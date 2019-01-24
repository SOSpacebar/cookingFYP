// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SmallShipAIController.generated.h"

/**
 * 
 */
class UBehaviorTreeComponent;

UCLASS()
class PROTOTYPE_4_21_API ASmallShipAIController : public AAIController
{
	GENERATED_BODY()

public:

	ASmallShipAIController();

	// In-line Getter Function
	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const { return blackBoardComponenet; };
	FORCEINLINE TArray<AActor*> GetPathArray() const { return pathPoints; };

	int32 currentPoint;

private:

	UBlackboardComponent *blackBoardComponenet;
	UBehaviorTreeComponent *behaviorTreeComponenet;

	// Blackboard Keys
	UPROPERTY(EditDefaultsOnly, Category = AI)
		FName nextLocation;

	TArray<AActor*> pathPoints;

	virtual void Possess(APawn *_pawn) override;
};