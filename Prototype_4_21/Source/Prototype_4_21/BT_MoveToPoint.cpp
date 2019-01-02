// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_MoveToPoint.h"
#include "AIDrone_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
//
//
//UBT_MoveToPoint::UBT_MoveToPoint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
//{
//
//	//NodeName = "MoveToPoint";
//	//bAllowStrafing = true;
//}
////
//EBTNodeResult::Type UBT_MoveToPoint::ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory)
//{
//	AAIDrone_Controller* aiCon = Cast<AAIDrone_Controller>(_ownerComp.GetAIOwner());
//
//	if (aiCon)
//	{
//		// Get BB component
//		UBlackboardComponent* blackBoardComp = aiCon->GetBlackboardComponent();
//
//		APlayerController* target = UGameplayStatics::GetPlayerController(GetWorld(), 0);
//
//		FVector direction = target->GetPawn()->GetActorLocation() - aiCon->GetPawn()->GetActorLocation();
//
//		const UBlackboardComponent* myBlackboard = _ownerComp.GetBlackboardComponent();
//		UObject* KeyValue = myBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
//		//aiCon->Move
//
//
//
//		FRotator rotation = FRotationMatrix::MakeFromX(direction).Rotator();
//		aiCon->GetPawn()->SetActorRotation(rotation);
//
//		return EBTNodeResult::Succeeded;
//	}
//
//	return EBTNodeResult::Failed;
//}
