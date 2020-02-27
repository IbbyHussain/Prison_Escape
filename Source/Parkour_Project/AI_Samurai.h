// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_PatrolPath.h"
#include "AI_Samurai.generated.h"

class AAI_Samurai_Guard_Weapon;
class AAI_Samurai_Guard_WeaponCase;
class UMaterial;
class AC_StaminaPickUp;
class UC_HealthComponent;
class AI_Samurai_Guard_Weapon;

UCLASS()
class PARKOUR_PROJECT_API AAI_Samurai : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAI_Samurai();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// A reference to the samurai weapon class
	UPROPERTY(EditAnywhere, Category = "Weapon") 
	AAI_Samurai_Guard_Weapon* SamuraiWeapon; 
	
	// A reference to the samurai case class
	UPROPERTY(EditAnywhere, Category = "Weapon") 
	AAI_Samurai_Guard_WeaponCase* SamuraiWeaponCase; 
	
	// ANIMATION -> A reference to the socket which is on the hip
	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
	FName WeaponAttachSocketName;

	// ANIMATION -> A reference to the socket which is right the hand
	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
	FName WeaponAttachSocket;
	
	// The function that will spawn the samurai weapon class
	UFUNCTION(BlueprintCallable) 
	void SpawnWeapon(TSubclassOf<AAI_Samurai_Guard_Weapon> SamuraiWeaponClass); 
	
	// The function that will spawn the samurai weapon case class
	UFUNCTION(BlueprintCallable) 
	void SpawnWeaponCase(TSubclassOf<AAI_Samurai_Guard_WeaponCase> SamuraiWeaponCaseClass);

	//DEATH->
	UFUNCTION(BlueprintCallable)
	void Death();

	//DEATH->
	FTimerHandle DeathTimerHandle;

	float DeathTimer;

	void DespawnAI();
	
	// MATERIALS
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterial* Black;

	//DEATH->
	UFUNCTION(BlueprintCallable)
	void SpawnStaminaPickup(TSubclassOf<AC_StaminaPickUp> StaminaPickupClass);

	AC_StaminaPickUp* StaminaPickupRef;

	UPROPERTY(VisibleDefaultsOnly, Category = "Pickup")
	FName StaminaPickupAttachSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Death")
	bool bHasAIDied;

	UC_HealthComponent* HealthComponent;

	UFUNCTION()
	void OnHealthUpdated( UC_HealthComponent* HealthComponent, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	AI_Samurai_Guard_Weapon* SamuariWeaponRef;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	AC_PatrolPath* patrol_path;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CheckForDeath();

	AC_PatrolPath* get_patrol_path();
	


};