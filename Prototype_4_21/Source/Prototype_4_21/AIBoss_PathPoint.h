// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI_PathPoint.h"
#include "AIBoss_PathPoint.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_4_21_API AAIBoss_PathPoint : public AAI_PathPoint
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PathPoint")
		uint8 direction;
};
