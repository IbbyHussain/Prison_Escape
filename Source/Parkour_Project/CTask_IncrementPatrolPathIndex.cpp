// Fill out your copyright notice in the Description page of Project Settings.


#include "CTask_IncrementPatrolPathIndex.h"
#include "C_SamuariAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI_Samurai.h"
#include "C_PatrolPoint.h"
#include "BlackBoardKeys.h"


UCTask_IncrementPatrolPathIndex::UCTask_IncrementPatrolPathIndex(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Increment Path Index");
}


EBTNodeResult::Type UCTask_IncrementPatrolPathIndex::ExecuteTask(UBehaviorTreeComponent & Owner, uint8 * NodeMemory)
{
	//Get the AI controlller
	AC_SamuariAIController* const Controller = Cast<AC_SamuariAIController>(Owner.GetAIOwner());
	AAI_Samurai* const AISamuraiReference = Cast<AAI_Samurai>(Controller->GetPawn());
	int const NumberOfPoints = AISamuraiReference->GetPatrolPointAI()->num();
	int const MinIndex = 0;
	int const MaxIndex = NumberOfPoints - 1;

	//Declare and Initialize blackboard index
	int index = Controller->get_blackboard()->GetValueAsInt(bb_Keys::PatrolPointIndex);
	if (index >= MaxIndex && Direction == EDirectionType::Forward)
	{
		Direction = EDirectionType::Reverse;
	}
	
	else if(index == MinIndex && Direction == EDirectionType::Reverse)
	{
		Direction = EDirectionType::Forward;
	}

	// if forward increment
	//if reverse decrement
	//use of modulus division so that the ai will loop around all points
	Controller->get_blackboard()->SetValueAsInt(bb_Keys::PatrolPointIndex, 
		(Direction == EDirectionType::Forward ? ++index : --index) % NumberOfPoints);

	//Finish With Success
	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
