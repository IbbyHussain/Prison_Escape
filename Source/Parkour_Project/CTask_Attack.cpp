// Fill out your copyright notice in the Description page of Project Settings.


#include "CTask_Attack.h"
#include "C_CombatInterface.h"
#include "C_SamuariAIController.h"
#include "AI_Samurai.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

UCTask_Attack::UCTask_Attack(FObjectInitializer  const& ObjectInitializer)
{
	NodeName = TEXT("CTask Attack");
}



EBTNodeResult::Type UCTask_Attack::ExecuteTask(UBehaviorTreeComponent & Owner, uint8 * NodeMemory)
{
	AC_SamuariAIController* const Controller = Cast<AC_SamuariAIController>(Owner.GetAIOwner());
	AAI_Samurai* const AISamuraiReference = Cast<AAI_Samurai>(Controller->GetPawn());

	// If AI is in range
	if (IC_CombatInterface* const ICombatInterfaceReference = Cast<IC_CombatInterface>(AISamuraiReference))
	{
		if (bHasMontageFinished(AISamuraiReference))
		{
			//execute task
			ICombatInterfaceReference->Execute_MeleeAttack(AISamuraiReference);
		}
	}

	FinishLatentTask(Owner, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
	
}

bool UCTask_Attack::bHasMontageFinished(AAI_Samurai * const AISamuraiReference)
{
	//checks to see if the montage is finished
	return AISamuraiReference->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(AISamuraiReference->GetAnimMontage());
}
