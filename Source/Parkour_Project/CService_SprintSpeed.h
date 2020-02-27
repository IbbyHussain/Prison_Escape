// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "CService_SprintSpeed.generated.h"

/**
 * 
 */
UCLASS()
class PARKOUR_PROJECT_API UCService_SprintSpeed : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UCService_SprintSpeed();

	void OnBecomeRelevant(UBehaviorTreeComponent& Owner, uint8* NodeMemory) override;

protected:

	FString GetStaticServiceDescription() const override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		float Speed;
	
};
