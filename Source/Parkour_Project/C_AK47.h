// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_AK47.generated.h"

class USkeletalMeshComponent;

UCLASS()
class PARKOUR_PROJECT_API AC_AK47 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_AK47();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* AK47Mesh;
	
	void Fire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
