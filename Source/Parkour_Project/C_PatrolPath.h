// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_PatrolPath.generated.h"

UCLASS()
class PARKOUR_PROJECT_API AC_PatrolPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_PatrolPath();

	FVector get_patrol_point(int const index) const;
	int num() const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	TArray<FVector> patrol_points;

};
