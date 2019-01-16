// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class PROTOTYPE_4_21_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		TSubclassOf<class USphereComponent> collisionComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
