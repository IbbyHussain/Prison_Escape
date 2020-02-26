// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "CTask_FindPatrolPathPoint.generated.h"

/**
 * 
 */
UCLASS()
class PARKOUR_PROJECT_API UCTask_FindPatrolPathPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UCTask_FindPatrolPathPoint(FObjectInitializer const& object_initializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner, uint8* node_memory) override;
	
};
