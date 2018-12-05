// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "Tools.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_4_21_API ATools : public AInteractableObject
{
	GENERATED_BODY()

public:
	ATools();

protected:

	// Mesh of the Object
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent *staticMesh;
};
