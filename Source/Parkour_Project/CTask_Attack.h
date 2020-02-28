// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CTask_Attack.generated.h"

class AAI_Samurai;

UCLASS()
class PARKOUR_PROJECT_API UCTask_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UCTask_Attack(FObjectInitializer const& ObjectInitializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Owner, uint8* NodeMemory) override;
private:
	bool bHasMontageFinished(AAI_Samurai* const AISamuraiReference);
	
};
