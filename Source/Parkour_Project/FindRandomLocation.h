// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "UObject/UObjectGlobals.h"
#include "FindRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class PARKOUR_PROJECT_API UFindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UFindRandomLocation(FObjectInitializer const& object_initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner_comp, uint8* node_memory);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"))
	float SearchRadius = 1500.0f;
	
};
