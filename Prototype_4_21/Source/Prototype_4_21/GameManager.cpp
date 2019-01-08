// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "Kismet/GameplayStatics.h"

AGameManager::AGameManager()
{

}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	SetCurrentState(EPlayState::E_PLAYING);
	SetCurrScenario(EScenario::E_INTRO);
}

void AGameManager::Tick(float _dt)
{
	Super::Tick(_dt);
}

EPlayState AGameManager::GetCurrentState() const
{
	return currentState;
}

void AGameManager::SetCurrentState(EPlayState _newState)
{
	currentState = _newState;
}

EScenario AGameManager::GetCurrScenario() const
{
	return currScenario;
}

void AGameManager::SetCurrScenario(EScenario _scenario)
{
	currScenario = _scenario;
}
