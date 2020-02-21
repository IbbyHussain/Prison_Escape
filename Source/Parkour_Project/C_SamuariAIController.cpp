// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SamuariAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Player_Character.h"

AC_SamuariAIController::AC_SamuariAIController(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT(""));
	if (obj.Succeeded())
	{
		behavior_tree = obj.Object;
	}

	behavior_tree_Component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));

	blackboard = object_initializer.CreateDefaultSubobject<UBlackBoardComponent>(this, TEXT("BlackboardComp"));



}

//
void AC_SamuariAIController::BeginPlay()
{
}

void AC_SamuariAIController::OnPossess(APawn * const pawn)
{
}

UBlackBoardComponent * AC_SamuariAIController::get_blackboard() const
{
	return blackboard;
}
