// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_SamuariAIController.generated.h"

/**
 * 
 */
UCLASS()
class PARKOUR_PROJECT_API AC_SamuariAIController : public AAIController
{
	GENERATED_BODY()

public:
	AC_SamuariAIController(FObjectInitializer const& object_initializer = FObjectInitializer::Get());
	
	void BeginPlay() override;
	
	void OnPossess(APawn* const pawn) override;

	class UBlackBoardComponent* get_blackboard() const;

private:
	UPROPERTY(EditInstnaceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* behavior_tree_Component;

	UPROPERTY(EditInstnaceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* behavior_tree;

	class UBlackBoardComponent* BlackBoard;










};
