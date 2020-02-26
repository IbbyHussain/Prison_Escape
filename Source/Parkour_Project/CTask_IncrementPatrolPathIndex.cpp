// Fill out your copyright notice in the Description page of Project Settings.


#include "CTask_IncrementPatrolPathIndex.h"
#include "C_SamuariAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI_Samurai.h"
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
	int const NumberOfPoints = AISamuraiReference->GetPatrolPointAI()->Num();
	int const MinIndex = 0;
	int const MaxIndex = NumberOfPoints - 1;

	

	return EBTNodeResult::Type();
}
