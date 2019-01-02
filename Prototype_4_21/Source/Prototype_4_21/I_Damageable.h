// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_Damageable.generated.h"

// This class does not need to be modified.
UINTERFACE(BluePrintable, MinimalAPI)
class UI_Damageable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class PROTOTYPE_4_21_API II_Damageable
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "I_Damageable")
		void TakeDamage(float _dmg);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "I_Damageable")
		float GetHealth();
private:
	float health;

};
