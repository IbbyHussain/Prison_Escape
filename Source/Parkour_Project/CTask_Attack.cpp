// Fill out your copyright notice in the Description page of Project Settings.


#include "CTask_Attack.h"
#include "C_CombatInterface.h"

UCTask_Attack::UCTask_Attack(FObjectInitializer  const& ObjectInitializer)
{
	NodeName = TEXT("CTask Attack");
}



EBTNodeResult::Type UCTask_Attack::ExecuteTask(UBehaviorTreeComponent & Owner, uint8 NodeMemory)
{
	return EBTNodeResult::Type();
}

bool UCTask_Attack::bHasMontageFinished(AAI_Samurai * const AISamuraiReference)
{
	return false;
}
