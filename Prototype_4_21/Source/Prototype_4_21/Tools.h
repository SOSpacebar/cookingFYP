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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	// Mesh of the Object
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent *staticMesh;

	//UFUNCTION(BlueprintCallable, Category = "JJInteraction/Interaction")
	virtual void Pickup_Implementation(class USceneComponent* _attachTo) override;

	//UFUNCTION(BlueprintCallable, Category = "JJInteraction/Interaction")
	virtual void Drop_Implementation() override;

	//UFUNCTION(BlueprintCallable, Category = "JJInteraction/Interaction")
	virtual void Interact_Implementation() override;

};
