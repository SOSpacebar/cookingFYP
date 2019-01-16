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

	virtual void OnConstruction(const FTransform& _transform) override;
	virtual void NotifyHit(UPrimitiveComponent* _myComp, AActor* _otherActor, UPrimitiveComponent* _otherComp, bool _bSelfMove, FVector _hitLocation, FVector _hitNormal, FVector _normalImpulse, const FHitResult& _hit) override;

	// Projectile speed
	UPROPERTY(EditAnywhere, Category = Projectile)
		float fSpeed;

	UPROPERTY(EditAnywhere, Category = Projectile)
		float fBounceSpeedLoss;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent *collisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		float collisionSize;

	// Projectile velocity vector
	FVector velocity;

	// Flag for reflected
	bool bReflected;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* _overlappedComp, class AActor* _otherActor, class UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
