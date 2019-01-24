// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIShipProps.generated.h"

UCLASS()
class PROTOTYPE_4_21_API AAIShipProps : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIShipProps();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = AIShipProps)
		class UBehaviorTree* behaviorTree;

	FORCEINLINE TArray<AActor*> GetPathArray() const { return pathPoints; };

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AIShipProps, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* model;

	UPROPERTY(EditAnywhere, Category = AIShipProps, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> pathPoints;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
