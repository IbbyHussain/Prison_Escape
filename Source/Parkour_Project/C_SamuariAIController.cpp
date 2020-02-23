// Fill out your copyright notice in the Description page of Project Settings.


#include "C_SamuariAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Player_Character.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "BlackBoardKeys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"

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

	//Perceptionsystem
	SetupPerceptionSystem();


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

//ONPERCEPTIONUPDATED
void AC_SamuariAIController::OnPerceptionUpdated(TArray<AActor*> const & UpdatedActors)
{
}

//SETUPPERCEPTION
void AC_SamuariAIController::SetupPerceptionSystem()
{
	//initializing components
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	//sets default values
	SightConfig->SightRadius = 500.0f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 50.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->SetMaxAge(5.0f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 900.0f;

	//AI will sense all types of objects
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	//Add sight configuration component to perception component
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AC_SamuariAIController::OnPerceptionUpdated);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	
}
