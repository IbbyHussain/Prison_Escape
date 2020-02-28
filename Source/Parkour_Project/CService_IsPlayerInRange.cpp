// Fill out your copyright notice in the Description page of Project Settings.


#include "CService_IsPlayerInRange.h"
#include "C_SamuariAIController.h"
#include "AI_Samurai.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlackBoardKeys.h"

UCService_IsPlayerInRange::UCService_IsPlayerInRange()
{
	NodeName = TEXT("CService Player Is In Melee Range");

	bNotifyBecomeRelevant = true;

	MeleeRange = 25.0f;
}

void UCService_IsPlayerInRange::OnBecomeRelevant(UBehaviorTreeComponent & Owner, uint8 * NodeMemory)
{
	Super::OnBecomeRelevant(Owner, NodeMemory);
}
