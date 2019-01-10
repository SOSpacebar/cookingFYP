// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BT_MoveToPoint.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_4_21_API UBT_MoveToPoint : public UBTTask_MoveTo
{
	GENERATED_BODY()


private:
	//virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory) override;

protected:
	///** blackboard key selector */
	//UPROPERTY(EditAnywhere, Category = Blackboard)
	//struct FBlackboardKeySelector BlackboardKey;

	//FORCEINLINE FName UBT_MoveToPoint::GetSelectedBlackboardKey() const
	//{
	//	return BlackboardKey.SelectedKeyName;
	//}
};
