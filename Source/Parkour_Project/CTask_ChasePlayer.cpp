// Fill out your copyright notice in the Description page of Project Settings.


#include "CTask_ChasePlayer.h"
#include "C_SamuariAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BlackBoardKeys.h"

UCTask_ChasePlayer::UCTask_ChasePlayer(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UCTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent & Owner, uint8 * node_memory)
{
	//Get target location
	AC_SamuariAIController* const Controller = Cast<AC_SamuariAIController>(Owner.GetAIOwner());
	FVector const PlayerLocation = Controller->get_blackboard()->GetValueAsVector(bb_Keys::TargetLocation);

	// Move to players location
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, PlayerLocation);

	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
