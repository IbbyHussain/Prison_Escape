// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AI_Samurai_Guard_WeaponCase.generated.h"

class AAI_Samurai;

UCLASS()
class PARKOUR_PROJECT_API AAI_Samurai_Guard_WeaponCase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAI_Samurai_Guard_WeaponCase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// A reference to this class
	UPROPERTY(EditAnywhere, Category = "Weapon")
	USkeletalMeshComponent* Weaponref;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AAI_Samurai* SamuraiRef;

	void Despawn();
};
