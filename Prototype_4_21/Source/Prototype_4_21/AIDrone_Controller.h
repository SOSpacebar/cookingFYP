// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIDrone_Controller.generated.h"


class UBehaviorTreeComponent;

/**
 * 
 */
UCLASS()
class PROTOTYPE_4_21_API AAIDrone_Controller : public AAIController
{
	GENERATED_BODY()

public:

	AAIDrone_Controller();

	// In-line Getter Function
	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const { return blackBoardComponenet; };
	FORCEINLINE TArray<AActor*> GetPathArray() const { return pathPoints; };

	void SetPlayerCoord(APawn* _pawn);

	int32 currentPoint;


protected:
	virtual void Possess(APawn *_pawn) override;

	UBlackboardComponent *blackBoardComponenet;
	UBehaviorTreeComponent *behaviorTreeComponenet;

	// Blackboard Keys
	UPROPERTY(EditDefaultsOnly, Category = AI)
		FName nextLocation;

	UPROPERTY(EditDefaultsOnly, Category = AI)
		FName player;

	TArray<AActor*> pathPoints;

};
