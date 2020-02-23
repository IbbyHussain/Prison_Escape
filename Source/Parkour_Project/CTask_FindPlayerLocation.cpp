// Fill out your copyright notice in the Description page of Project Settings.


#include "CTask_FindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "C_SamuariAIController.h"
#include "GameFramework/Character.h"
#include "Player_Character.h"
#include "BlackBoardKeys.h"

//CONSTRUCTOR
UCTask_FindPlayerLocation::UCTask_FindPlayerLocation(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Player Location");

	bIsSearchingRandomLocation = false;

	SearchRadius = 150.0f;
}

//TASK->find player's location
EBTNodeResult::Type UCTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent & Owner, uint8 * node_memory)
{
	//Get player's character and AI's controller
	ACharacter* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto const Controller = Cast<AC_SamuariAIController>(Owner.GetAIOwner());

	//Get player location
	FVector const PlayerLocation = Player->GetActorLocation();

	if(bIsSearchingRandomLocation)
	{
		FNavLocation Location;

		//Get navigation system and call a random location near player
		UNavigationSystemV1* const NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());

		if (NavigationSystem->GetRandomPointInNavigableRadius(PlayerLocation, SearchRadius, Location, nullptr))
		{
			Controller->get_blackboard()->SetValueAsVector(bb_Keys::TargetLocation, Location.Location);
		}
	}

	else
	{
		Controller->get_blackboard()->SetValueAsVector(bb_Keys::TargetLocation, PlayerLocation);
	}
	
	//Finish task
	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
