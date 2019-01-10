// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameManager.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EPlayState : uint8
{
	E_PLAYING,
	E_GAMEOVER,
	E_WON,
	E_NONE
};

UENUM(BlueprintType)
enum class EScenario : uint8
{
	E_INTRO,
	E_EVENT1,
	E_EVENT2,
	E_NONE
};

UCLASS()
class PROTOTYPE_4_21_API AGameManager : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameManager();

	UFUNCTION(BlueprintPure, Category = "GAMEMANAGER")
	EPlayState GetCurrentState() const;

	void SetCurrentState(EPlayState _newState);

	UFUNCTION(BlueprintPure, Category = "GAMEMANAGER")
	EScenario GetCurrScenario() const;

	void SetCurrScenario(EScenario _scenario);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GAMEMANAGER")
	void RunEvent();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float _dt) override;


	EPlayState currentState;
	EScenario currScenario;




};
