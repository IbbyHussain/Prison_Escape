// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "CTask_IncrementPathIndex.generated.h"

/**
 * 
 */
UCLASS()
class PARKOUR_PROJECT_API UCTask_IncrementPathIndex : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UCTask_IncrementPathIndex(FObjectInitializer const& object_initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner, uint8* node_memory) override;
	
private:
	enum class EDirectionType
	{
		Forward, Reverse
	};

	EDirectionType Direction = EDirectionType::Forward;

};
