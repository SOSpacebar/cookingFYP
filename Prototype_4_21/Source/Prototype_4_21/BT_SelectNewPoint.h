// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_SelectNewPoint.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_4_21_API UBT_SelectNewPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory) override;



};
