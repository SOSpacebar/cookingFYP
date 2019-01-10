// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "I_Damageable.h"

#include "AIDrone.generated.h"

UENUM(BlueprintType)
enum class AI_DRONESTATES : uint8
{
	IDLE = 0 UMETA(DisplayName = "IDLE"),
	COMBAT UMETA(DisplayName = "COMBAT"),
	DEAD UMETA(DisplayName = "DEAD"),
	NONE UMETA(DisplayName = "NONE")
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

	APlayerController* target;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = AI)
		class UBehaviorTree* behaviorTree;

	UPROPERTY(VisibleAnywhere, Category = AI)
		class UPawnSensingComponent* sensor;

	UPROPERTY(VisibleAnywhere, Category = AI)
		AI_DRONESTATES state;


	// Interface for II_Damageable
	virtual void TakeDamage_Implementation(float _dmg) override;
	virtual float GetHealth_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = AI)
		void TestDamage();
private:
	UFUNCTION()
		void OnPlayerSighted(APawn *_pawn);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		float health;
};
