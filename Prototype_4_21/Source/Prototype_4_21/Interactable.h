// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROTOTYPE_4_21_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "JJInteraction/Interaction")
		void PickupObject(class USceneComponent* AttachTo);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "JJInteraction/Interaction")
		void DropObject();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "JJInteraction/Interaction")
		void InteractObject();
};