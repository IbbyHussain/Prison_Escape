// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AI_Samurai_Guard_Weapon.generated.h"

//Define external classes here:

class AAI_Samurai;

UCLASS()
class PARKOUR_PROJECT_API AAI_Samurai_Guard_Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAI_Samurai_Guard_Weapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// A reference to this class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* Weaponref;
	
	AAI_Samurai* AISamuraiRef;

	UPROPERTY(EditAnywhere, Category = "Collision")
	UBoxComponent* BoxComponent;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void test();

};
