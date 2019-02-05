// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBT_DroneSelectNextPoint.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_4_21_API UMyBT_DroneSelectNextPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory) override;
};
