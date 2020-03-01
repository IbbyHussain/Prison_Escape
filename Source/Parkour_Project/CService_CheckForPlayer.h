// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "CService_CheckForPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PARKOUR_PROJECT_API UCService_CheckForPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UCService_CheckForPlayer();

	virtual void TickNode(UBehaviorTreeComponent& Owner, uint8* NodeMemory, float DeltaSeconds) override;
};
