// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_StaminaPickUp.generated.h"

class UParticleSystemComponent;
class UBoxComponent;
class UStaticMeshComponent;
class APlayer_Character;
class C_StaminaPickUp;


UCLASS()
class PARKOUR_PROJECT_API AC_StaminaPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_StaminaPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* StaminaPickupStaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	UParticleSystemComponent* StaminaPickupEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	UBoxComponent* BoxComponent;

	AC_StaminaPickUp* Self;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	APlayer_Character* PlayerCharacterRef;

};
