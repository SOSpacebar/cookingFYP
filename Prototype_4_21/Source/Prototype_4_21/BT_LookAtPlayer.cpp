// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_LookAtPlayer.h"
#include "AIDrone_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


EBTNodeResult::Type UBT_LookAtPlayer::ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory)
{
	AAIDrone_Controller* aiCon = Cast<AAIDrone_Controller>(_ownerComp.GetAIOwner());

	if (aiCon)
	{
		// Get BB component
		UBlackboardComponent* blackBoardComp = aiCon->GetBlackboardComponent();

		APlayerController* target = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		FVector direction = target->GetPawn()->GetActorLocation() - aiCon->GetPawn()->GetActorLocation();
		FRotator rotation = FRotationMatrix::MakeFromX(direction).Rotator();
		aiCon->GetPawn()->SetActorRotation(rotation);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
