// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	fSpeed = 3000.f;
	fBounceSpeedLoss = 0.5f;

	collisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	collisionComp->InitSphereRadius(5.f);
	collisionComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
	//collisionComp->OnComponentEndOverlap.AddDynamic(this, &AProjectile::OnOverlap);
	RootComponent = collisionComp;

	InitialLifeSpan = 3.0f;
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* _overlappedComp, AActor * _otherActor, UPrimitiveComponent * _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult & _sweepResult)
{
	if ((_otherActor != NULL) && (_otherActor != this) && (_otherComp != NULL))
	{
		if (_otherComp->IsSimulatingPhysics())
		{
			_otherComp->AddImpulseAtLocation(velocity * 100.f, GetActorLocation());
			Destroy();
		}

		Destroy();
	}
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FColor LineColor = bReflected ? FColor::Red : FColor::Green;
	//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + velocity * DeltaTime, LineColor, false, 2.f, 0, 1.f);
	SetActorLocation(GetActorLocation() + velocity * DeltaTime, true);
}

void AProjectile::OnConstruction(const FTransform & _transform)
{
	Super::OnConstruction(_transform);
	velocity = GetActorForwardVector() * fSpeed;
}

void AProjectile::NotifyHit(UPrimitiveComponent * _myComp, AActor * _otherActor, UPrimitiveComponent * _otherComp, bool _bSelfMove, FVector _hitLocation, FVector _hitNormal, FVector _normalImpulse, const FHitResult & _hit)
{
	Super::NotifyHit(_myComp, _otherActor, _otherComp, _bSelfMove, _hitLocation, _hitNormal, _normalImpulse, _hit);


	// Reflect the projectile because we hit a non-physics object

	FVector ReflectedVelocity = fBounceSpeedLoss * (-2 * FVector::DotProduct(velocity, _hitNormal) * _hitNormal + velocity);
	velocity = ReflectedVelocity;
	ReflectedVelocity.Normalize();
	SetActorRotation(ReflectedVelocity.Rotation());
	bReflected = true;
}

