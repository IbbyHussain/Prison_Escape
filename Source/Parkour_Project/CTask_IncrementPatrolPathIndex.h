// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "CTask_IncrementPatrolPathIndex.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PARKOUR_PROJECT_API UCTask_IncrementPatrolPathIndex : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UCTask_IncrementPatrolPathIndex(FObjectInitializer const& ObjectInitializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner, uint8* node_memory) override;
private:
	enum class EDirectionType
	{
		Forward, Reverse
	};

	EDirectionType Direction = EDirectionType::Forward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	bool bDirectional;


};
