// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "I_Damageable.h"
#include "SpawnVolume.h"
#include "AIDrone.generated.h"

UENUM(BlueprintType)
enum class AI_DRONESTATES : uint8
{
	IDLE = 0 UMETA(DisplayName = "IDLE"),
	COMBAT UMETA(DisplayName = "COMBAT"),
	DEAD UMETA(DisplayName = "DEAD"),
	NONE UMETA(DisplayName = "NONE")
};

UENUM(BlueprintType)
enum class AI_TYPE : uint8
{
	EASY = 0 UMETA(DisplayName = "EASY"),
	INTERMEDIATE = 0 UMETA(DisplayName = "INTERMEDIATE"),
	HARD = 0 UMETA(DisplayName = "HARD"),
	BOSS = 0 UMETA(DisplayName = "BOSS"),
	NONE = 0 UMETA(DisplayName = "NONE"),
};

UCLASS()
class PROTOTYPE_4_21_API AAIDrone : public ACharacter, public II_Damageable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIDrone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float _dt) override;

	APlayerController* playerController;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = AI)
		class UBehaviorTree* behaviorTree;

	UPROPERTY(VisibleAnywhere, Category = AI)
		class UPawnSensingComponent* sensor;

	UPROPERTY(EditAnywhere, Category = AI)
		AI_DRONESTATES state;

	UPROPERTY(EditAnywhere, Category = AI)
		AI_TYPE type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		TSubclassOf<class AProjectile> projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		class UParticleSystemComponent* particleDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		class USoundCue* particleDeathSound;

	// Interface for II_Damageable
	virtual void TakeDamage_Implementation(float _dmg) override;
	virtual float GetHealth_Implementation() override;

	// True = Right Side, False = Left Side
	FORCEINLINE void SetSpawnSide(ESpawnSide _side) { spawnSide = _side; };
	FORCEINLINE ESpawnSide GetSpawnSide() { return spawnSide; };

	FORCEINLINE float GetFireRate() { return fireRate; };

	FORCEINLINE uint8 GetAvailableShots() { return availableShots; };

	UFUNCTION(BlueprintCallable, Category = AI)
		void TestDamage();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
		bool isDead;
private:
	UFUNCTION()
		void OnPlayerSighted(APawn *_pawn);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		float health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		float fireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		uint8 minShots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		uint8 maxShots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		ESpawnSide spawnSide;

	float removeTimer;
	uint8 availableShots;

	class UAudioComponent* audioComponent;
};
