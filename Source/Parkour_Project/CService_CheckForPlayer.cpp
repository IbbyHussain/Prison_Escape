// Fill out your copyright notice in the Description page of Project Settings.


#include "CService_CheckForPlayer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AI_Samurai.h"
#include "C_SamuariAIController.h"
#include "Player_Character.h"
#include "BlackBoardKeys.h"


UCService_CheckForPlayer::UCService_CheckForPlayer()
{
	bCreateNodeInstance = true;
}

void UCService_CheckForPlayer::TickNode(UBehaviorTreeComponent & Owner, uint8 * NodeMemory, float DeltaSeconds)
{
	//Gets a reference to AI Controller
	AC_SamuariAIController* EnemyPC = Cast<AC_SamuariAIController>(Owner.GetAIOwner());

	//if controller is not null
	if(EnemyPC)
	{
		//Gets Reference to the Player
		APlayer_Character* PlayerCharacterReference = Cast<APlayer_Character>(GetWorld()->GetFirstPlayerController()->GetPawn());

		// If the Player is not Null
		//Important so the AI can go back to patroling if the player runs away
		if (PlayerCharacterReference)
		{
			//Sets Value of the Player Reference from blackboard
			Owner.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(bb_Keys::PlayerRef, PlayerCharacterReference);
			//UE_LOG(LogTemp, Log, TEXT("Seen Player"));
		}
	}


}
