// Fill out your copyright notice in the Description page of Project Settings.


#include "CTask_FindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "C_SamuariAIController.h"
#include "GameFramework/Character.h"
#include "BlackBoardKeys.h"

//CONSTRUCTOR
UCTask_FindPlayerLocation::UCTask_FindPlayerLocation(FObjectInitializer const& object_initializer)
{
	bIsSearchingRandomLocation = false;

	SearchRadius = 150.0f;
}

//TASK->find player's location
EBTNodeResult::Type UCTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent & Owner, uint8 * node_memory)
{
	return EBTNodeResult::Type();
}
