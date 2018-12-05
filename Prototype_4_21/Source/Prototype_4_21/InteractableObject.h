// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Environment.h"
#include "Interactable.h"
#include "InteractableObject.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_4_21_API AInteractableObject : public AEnvironment, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// What kind of action is this?
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName objectID;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//// What happens when the object is interacted.
	//UFUNCTION(BlueprintImplementableEvent)
	//void Interact();

	virtual FString GetInteractMessage() override;

	virtual void StartInteract() override;

	virtual void EndInteract() override;


	UFUNCTION(BlueprintCallable, Category = "Info")
	FString GetInteractableText() const;
};
