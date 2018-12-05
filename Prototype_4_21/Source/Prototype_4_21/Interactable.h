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
	// Returns Message of the intractable object.
	//UFUNCTION(BlueprintCallable, Category = "Info")
		virtual FString GetInteractMessage() = 0;

	// Starts execution for the interaction.
	//UFUNCTION(BlueprintCallable, Category = "Interaction")
		virtual void StartInteract() = 0;

	// End execution of the interaction.
	//UFUNCTION(BlueprintCallable, Category = "Interaction")
		virtual void EndInteract() = 0;
};
