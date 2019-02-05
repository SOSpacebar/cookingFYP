// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_Attack.h"
#include "AIDrone_Controller.h"
#include "AIDrone.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

EBTNodeResult::Type UBT_Attack::ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory)
{
	//AAIDrone_Controller* aiCon = Cast<AAIDrone_Controller>(_ownerComp.GetAIOwner());
	//AAIDrone* aiDrone = Cast<AAIDrone>(aiCon->GetPawn());
	timer = 0.f;
	shotsFiredCounter = 0.f;
	bNotifyTick = true;

	return EBTNodeResult::InProgress;
}

void UBT_Attack::TickTask(UBehaviorTreeComponent & _ownerComp, uint8 * _nodeMemory, float _dt)
{
	Super::TickTask(_ownerComp, _nodeMemory, _dt);

	AAIDrone_Controller* aiCon = Cast<AAIDrone_Controller>(_ownerComp.GetAIOwner());
	AAIDrone* aiDrone = Cast<AAIDrone>(aiCon->GetPawn());

	if (aiCon)
	{

		// Get BB component
		UBlackboardComponent* blackBoardComp = aiCon->GetBlackboardComponent();
		UWorld* const world = GetWorld();

		if (world)
		{
			timer += _dt;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("PEWPEWP + %d"), aiDrone->GetFireRate()));
			if (timer > aiDrone->GetFireRate())
			{
				FActorSpawnParameters spawnParams;
				spawnParams.Owner = aiCon;
				spawnParams.Instigator = aiCon->Instigator;

				FVector spawnLocation = aiDrone->GetActorLocation();
				FRotator spawnRotation = aiDrone->GetActorRotation();

				if (aiDrone->projectile)
				{
					world->SpawnActor<AProjectile>(aiDrone->projectile, spawnLocation, spawnRotation, spawnParams);
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("NULLLLLLLLLL")));
				}

				shotsFiredCounter++;
				timer = 0.f;
			}
		}

		if (shotsFiredCounter >= aiDrone->GetAvailableShots())
		{
			FinishLatentTask(_ownerComp, EBTNodeResult::Succeeded);
		}
	}
}
