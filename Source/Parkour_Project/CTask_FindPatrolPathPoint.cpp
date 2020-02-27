// Fill out your copyright notice in the Description page of Project Settings.


#include "CTask_FindPatrolPathPoint.h"
#include "C_SamuariAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI_Samurai.h"
#include "BlackBoardKeys.h"


UCTask_FindPatrolPathPoint::UCTask_FindPatrolPathPoint(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find patrol path point C");
}


EBTNodeResult::Type UCTask_FindPatrolPathPoint::ExecuteTask(UBehaviorTreeComponent & Owner, uint8 * node_memory)
{
	//get ai controller
	AC_SamuariAIController* const Controller = Cast<AC_SamuariAIController>(Owner.GetAIOwner());

	//get current patrol path index from blackboard
	int const index = Controller->get_blackboard()->GetValueAsInt(bb_Keys::patrol_path_index);

	// use index to get current patrol path from ai ref from patrol path
	AAI_Samurai* const AISamurai = Cast<AAI_Samurai>(Controller->GetPawn());
	FVector const point = AISamurai->get_patrol_path()->get_patrol_point(index);

	//transform point to global position
	FVector const global_point = AISamurai->get_patrol_path()->GetActorTransform().TransformPosition(point);

	Controller->get_blackboard()->SetValueAsVector(bb_Keys::patrol_path_vector, global_point);

	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
