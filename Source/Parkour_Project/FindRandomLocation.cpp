// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomLocation.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "C_SamuariAIController.h"
//#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BlackBoardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"

//Constructor
UFindRandomLocation::UFindRandomLocation(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UFindRandomLocation::ExecuteTask(UBehaviorTreeComponent & Owner_comp, uint8 * node_memory)
{
	// get AI controller and AI
	auto const cont = Cast<AC_SamuariAIController>(Owner_comp.GetAIOwner());
	auto const AI = cont->GetPawn();

	//get AI location to use as starting location
	FVector const Origin = AI->GetActorLocation();
	FNavLocation Loc;

	//get navigation system and generate a random location within nav mesh
	UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (nav_sys->GetRandomPointInNavigableRadius(Origin, SearchRadius, Loc, nullptr))
	{
		cont->get_blackboard()->SetValueAsVector(bb_Keys::TargetLocation, Loc.Location);

	}
	
	//finish task
	FinishLatentTask(Owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
