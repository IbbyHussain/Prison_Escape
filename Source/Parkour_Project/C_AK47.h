// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_AK47.generated.h"

class USkeletalMeshComponent;
class UDamageType;
class UParticleSystem;
class APlayer_Character;
class AC_AK47Mag;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AK47")
	TSubclassOf<UDamageType> DefaultDamage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "AK47")
	FName MuzzleSocket;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "AK47")
	FName TracerTargetName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AK47")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AK47")
	UParticleSystem* DefaultImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AK47")
	UParticleSystem* FleshImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AK47")
	UParticleSystem* TraceEffect;

	UPROPERTY(EditDefaultsOnly, Category = "AK47")
	TSubclassOf<UCameraShake> FireCameraShake;

	float BaseDamage;

	void Fire();

	FTimerHandle FiringTimer;

	UPROPERTY(EditDefaultsOnly, Category = "AK47")
	float FireRate;

	//RPM Bullets per minute
	float LastFireTime;

	float TimeBetweenShots;

	APlayer_Character *PlayerCharacterRef;

	UFUNCTION(BlueprintCallable)
	void SpawnMag(TSubclassOf<AC_AK47Mag>MagClass);

	AC_AK47Mag* MagRef;

	UPROPERTY(VisibleDefaultsOnly, Category = "AK47")
	FName MagAttachSocket;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

	void StartFire();

	void StopFire();

};
