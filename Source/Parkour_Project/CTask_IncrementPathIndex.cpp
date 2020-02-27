// Fill out your copyright notice in the Description page of Project Settings.


#include "CTask_IncrementPathIndex.h"
#include "C_SamuariAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI_Samurai.h"
#include "BlackBoardKeys.h"


UCTask_IncrementPathIndex::UCTask_IncrementPathIndex(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Increment path index");
}


EBTNodeResult::Type UCTask_IncrementPathIndex::ExecuteTask(UBehaviorTreeComponent & Owner, uint8 * node_memory)
{
	//get ai controller
	AC_SamuariAIController* const Controller = Cast<AC_SamuariAIController>(Owner.GetAIOwner());
	AAI_Samurai* const AISamurai = Cast<AAI_Samurai>(Controller->GetPawn());
	int const no_of_points = AISamurai->get_patrol_path()->num();
	int const min_index = 0;
	int const max_index = no_of_points - 1;

	//get and set blackboard index key
	int index = Controller->get_blackboard()->GetValueAsInt(bb_Keys::patrol_path_index);

	if(index >= max_index && Direction == EDirectionType::Forward)
	{
		Direction = EDirectionType::Reverse;
	}

	else if(index == min_index && Direction == EDirectionType::Reverse)
	{
		Direction = EDirectionType::Forward;
	}

	Controller->get_blackboard()->SetValueAsInt(bb_Keys::patrol_path_index,
		(Direction == EDirectionType::Forward ? ++index : --index) % no_of_points);


	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
