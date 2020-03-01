// Fill out your copyright notice in the Description page of Project Settings.


#include "CTask_ChasePlayer.h"
#include "C_SamuariAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BlackBoardKeys.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Player_Character.h"

UCTask_ChasePlayer::UCTask_ChasePlayer(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UCTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent & Owner, uint8 * node_memory)
{
	//Get target location
	/*AC_SamuariAIController* const Controller = Cast<AC_SamuariAIController>(Owner.GetAIOwner());
	FVector const PlayerLocation = Controller->get_blackboard()->GetValueAsVector(bb_Keys::TargetLocation);*/

	// Move to players location
	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, PlayerLocation);

	// Complex move to players location
	//Reference to AI Controller
	AC_SamuariAIController* const Controller = Cast<AC_SamuariAIController>(Owner.GetAIOwner());
	
	//Get Reference to the Player Character
	APlayer_Character * PlayerCharacterReference = Cast<APlayer_Character>(Owner.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(bb_Keys::PlayerRef));

	// If the player character is not null
	if (PlayerCharacterReference)
	{
		// moves  the AI directly to the player character
		Controller->MoveToActor(PlayerCharacterReference, 50.0f, true, true, true, 0, true);
		

		FinishLatentTask(Owner, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	
	/*FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;*/

	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
