// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SamuariAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Player_Character.h"

//CONSTRUCTOR
AC_SamuariAIController::AC_SamuariAIController(FObjectInitializer const& object_initializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/AI/AI_Samuari/BT_AISamuari.BT_AISamuari'"));
	if (obj.Succeeded())
	{
		behavior_tree = obj.Object;
	}

	behavior_tree_Component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));

	AIblackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));



}

//BEGINPLAY
void AC_SamuariAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(behavior_tree);
	behavior_tree_Component->StartTree(*behavior_tree);
}

//ONPOSSESS
void AC_SamuariAIController::OnPossess(APawn * const pawn)
{
	Super::OnPossess(pawn);
	if(AIblackboard)
	{
		AIblackboard->InitializeBlackboard(*behavior_tree->BlackboardAsset);
	}
}


UBlackboardComponent * AC_SamuariAIController::get_blackboard() const
{
	return AIblackboard;
}
