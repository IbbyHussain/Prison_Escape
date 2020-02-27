// Fill out your copyright notice in the Description page of Project Settings.


#include "CService_SprintSpeed.h"
#include "AI_Samurai.h"
#include "C_SamuariAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

//CONSTRUCTOR
UCService_SprintSpeed::UCService_SprintSpeed()
{
	NodeName = TEXT("Service Sprint Speed C");

	bNotifyBecomeRelevant = true;

	Speed = 600;
}

void UCService_SprintSpeed::OnBecomeRelevant(UBehaviorTreeComponent & Owner, uint8 * NodeMemory)
{
	Super::OnBecomeRelevant(Owner, NodeMemory);
	auto const Controller = Owner.GetAIOwner();
	AAI_Samurai* const AISamuraiReference = Cast<AAI_Samurai>(Controller->GetPawn());
	AISamuraiReference->GetCharacterMovement()->MaxWalkSpeed = Speed;
	AISamuraiReference->SprintStatusTrue();
}

FString UCService_SprintSpeed::GetStaticServiceDescription() const
{
	return FString("Change AI speed to sprinting");
}
