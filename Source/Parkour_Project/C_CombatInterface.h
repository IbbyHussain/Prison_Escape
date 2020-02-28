// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "C_CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class PARKOUR_PROJECT_API UC_CombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PARKOUR_PROJECT_API IC_CombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	int MeleeAttack();
};
