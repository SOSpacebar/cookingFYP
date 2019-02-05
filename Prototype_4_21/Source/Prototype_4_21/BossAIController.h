// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIDrone_Controller.h"
#include "BossAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_4_21_API ABossAIController : public AAIDrone_Controller
{
	GENERATED_BODY()

private:
	void Possess(APawn *_pawn) override;
};
