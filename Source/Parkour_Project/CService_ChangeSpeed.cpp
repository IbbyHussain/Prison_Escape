// Fill out your copyright notice in the Description page of Project Settings.


#include "CService_ChangeSpeed.h"
#include "AI_Samurai.h"
#include "C_SamuariAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

//CONSTRUCTOR
UCService_ChangeSpeed::UCService_ChangeSpeed()
{
	NodeName = TEXT("Service change speed");

	bNotifyBecomeRelevant = true;

	Speed = 600.0f;
}

void UCService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent & Owner, uint8 * NodeMemory)
{
	Super::OnBecomeRelevant(Owner, NodeMemory);
	auto const Controller = Owner.GetAIOwner();
	AAI_Samurai* const AISamuraiReference = Cast<AAI_Samurai>(Controller->GetPawn());
	AISamuraiReference->GetCharacterMovement()->MaxWalkSpeed = Speed;
}

FString UCService_ChangeSpeed::GetStaticServiceDescription() const
{
	return FString("Change the AI Speed");
}
