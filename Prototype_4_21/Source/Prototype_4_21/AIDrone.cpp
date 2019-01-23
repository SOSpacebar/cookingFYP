// Fill out your copyright notice in the Description page of Project Settings.

#include "AIDrone.h"
#include "AIDrone_Controller.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "Kismet/GameplayStatics.h"
#include "IXRTrackingSystem.h"

// Sets default values
AAIDrone::AAIDrone()
{
	//Initialize sensor
	sensor = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	sensor->SetPeripheralVisionAngle(90.f);

	state = AI_DRONESTATES::IDLE;
	playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	health = 100.f;

	PrimaryActorTick.bCanEverTick = true;
	SetSpawnSide(ESpawnSide::E_NONE);
}

// Called when the game starts or when spawned
void AAIDrone::BeginPlay()
{
	Super::BeginPlay();
	
	if (sensor)
	{
		sensor->OnSeePawn.AddDynamic(this, &AAIDrone::OnPlayerSighted);
	}
}

void AAIDrone::Tick(float _dt)
{
	if (!playerController)
	{
		playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	}

	//Check is there a VR headset
	if (GEngine->XRSystem && GEngine->XRSystem->GetHMDDevice())
	{
		FVector direction;
		FQuat playerQuat;
		FVector playerVector;

		GEngine->XRSystem->GetCurrentPose(IXRTrackingSystem::HMDDeviceId, playerQuat, playerVector);

		FVector finalloc = playerQuat.RotateVector(playerVector) + playerController->PlayerCameraManager->GetCameraLocation();
		direction = finalloc - this->GetActorLocation();
		FRotator rotation = FRotationMatrix::MakeFromX(direction).Rotator();

		this->SetActorRotation(rotation);
	}
	else
	{
		FVector direction = playerController->PlayerCameraManager->GetCameraLocation() - this->GetActorLocation();
		FRotator rotation = FRotationMatrix::MakeFromX(direction).Rotator();
		this->SetActorRotation(rotation);
	}

	if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->IsInputKeyDown(EKeys::O))
	{
		TestDamage();
	}
}

// Called to bind functionality to input
void AAIDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIDrone::TakeDamage_Implementation(float _dmg)
{
	if (health)
	{
		health -= _dmg;
		
		if (health <= 100)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Health : %f"), health));
			//DIIEEEE
			if (health <= 0)
			{
				Destroy();
			}
		}
	}
}

float AAIDrone::GetHealth_Implementation()
{
	return health;
}

void AAIDrone::TestDamage()
{
	health -= 20;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Health : %f"), health));
}

void AAIDrone::OnPlayerSighted(APawn * _pawn)
{
	// Get reference to player
	AAIDrone_Controller* aiCon = Cast<AAIDrone_Controller>(GetController());

	// Get BB component
	UBlackboardComponent* blackBoardComp = aiCon->GetBlackboardComponent();

	if (aiCon)
	{

		aiCon->SetPlayerCoord(_pawn);
		state = AI_DRONESTATES::COMBAT;

		//TESTING
		if (state == AI_DRONESTATES::COMBAT)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("I SEE YOU"));
		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("I SEE YOU"));
		}
	}

	// Set key value in black board.
	blackBoardComp->SetValue<UBlackboardKeyType_Enum>(blackBoardComp->GetKeyID("State"), static_cast<UBlackboardKeyType_Enum::FDataType>(state));
}

