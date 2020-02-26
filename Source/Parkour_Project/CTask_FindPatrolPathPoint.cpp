// Fill out your copyright notice in the Description page of Project Settings.


#include "CTask_FindPatrolPathPoint.h"
#include "C_SamuariAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI_Samurai.h"
#include "BlackBoardKeys.h"

//CONSTRUCTOR
UCTask_FindPatrolPathPoint::UCTask_FindPatrolPathPoint(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Patrol Path Point");
}


EBTNodeResult::Type UCTask_FindPatrolPathPoint::ExecuteTask(UBehaviorTreeComponent & Owner, uint8 * node_memory)
{
	//Get AI controller 
	AC_SamuariAIController* const Controller = Cast<AC_SamuariAIController>(Owner.GetAIOwner());

	//Get the current patrol path index from the blackboard
	int const index = Controller->get_blackboard()->GetValueAsInt(bb_Keys::PatrolPointIndex);

	//Use PatrolPointIndex variable to get current patrol point
	AAI_Samurai* const AISamuraiReference = Cast<AAI_Samurai>(Controller->GetPawn());
	FVector const Point = AISamuraiReference->GetPatrolPathAI()->GetPatrolPoints(index);

	//Covert Local vector to global vector
	FVector const GlobalPoint = AISamuraiReference->GetPatrolPathAI()->GetActorTransform().TransformPosition(Point);

	Controller->get_blackboard()->SetValueAsVector(bb_Keys::PatrolPoint, GlobalPoint);

	//Finish task with success
	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
