// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_LookAtPlayer.h"
#include "AIDrone_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "IXRTrackingSystem.h"

EBTNodeResult::Type UBT_LookAtPlayer::ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory)
{
	AAIDrone_Controller* aiCon = Cast<AAIDrone_Controller>(_ownerComp.GetAIOwner());

	if (aiCon)
	{
		// Get BB component
		UBlackboardComponent* blackBoardComp = aiCon->GetBlackboardComponent();

		APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		FVector direction;

		// Check is there a VR set.
		if (GEngine->XRSystem->GetHMDDevice())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("YEEEEEEEEEEEEET")));
			FQuat playerQuat;
			FVector playerVector;
			GEngine->XRSystem->GetCurrentPose(IXRTrackingSystem::HMDDeviceId, playerQuat, playerVector);
			FVector finalloc = playerQuat.RotateVector(playerVector) + playerController->PlayerCameraManager->GetCameraLocation();
			direction = finalloc - aiCon->GetPawn()->GetActorLocation();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("NOOOOOOOOO")));
			direction = playerController->GetPawn()->GetActorLocation() - aiCon->GetPawn()->GetActorLocation();
		}
		
		FRotator rotation = FRotationMatrix::MakeFromX(direction).Rotator();
		aiCon->GetPawn()->SetActorRotation(rotation);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
