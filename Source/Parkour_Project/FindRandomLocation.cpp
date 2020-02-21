// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "C_SamuariAIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include ""

EBTNodeResult::Type UFindRandomLocation::ExecuteTask(UBehaviorTreeComponent & Owner_comp, uint8 * node_memory)
{
	return EBTNodeResult::Type();
}
