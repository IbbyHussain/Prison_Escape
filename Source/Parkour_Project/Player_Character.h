// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class AC_AK47;
class AC_AK47Mag;
class APlayer_Character;
class AC_Kabuto;

UCLASS()
class PARKOUR_PROJECT_API APlayer_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//MOVEMENT-> moveing forward and backward
	void MoveForward(float Value);

	//MOVEMENT-> moveing left and right
	void MoveRight(float Value);

	//CAMERA-> A reference to the camera
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComp;

	//CAMERA-> A reference to the spring arm
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComp;

	//DoubleJump-> will set a custom functionality
	virtual void Landed(const FHitResult& Hit) override;

	
	UPROPERTY()
	float JumpAnimationTime;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
	bool bCanJump;

	

	// STAMINA-> the current stamina value                                           
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float CurrentStamina;

	//ZOOM-> zoomed in value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zoom")
	float ZoomedFOV;

	//ZOOM->
	UPROPERTY(EditDefaultsOnly, Category = "Zoom", meta = (ClampMin = 0.1, ClampMax = 100))
	float ZoomInterpSpeed;

	//ZOOM-> default field of view
	float DefaultFOV;

	//ZOOM-> A boolean to control zooming in
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Zoom")
	bool bCanZoomIn;

	//ZOOM->
	void BeginZoom();

	//ZOOM->
	void EndZoom();

	AC_AK47* AK47;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AK47")
	TSubclassOf<AC_AK47> AK47Class;

	UPROPERTY(VisibleDefaultsOnly)
	FName WeaponAttachSocketName;

	//AMMO
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AK47")
	int32 LoadedAmmo;

	//AMMO
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AK47")
	int32 MaxAmmo;

	//RELOADING
	void Reload();

	//RELOADING
	void ReloadDuration();

	//RELOADING
	FTimerHandle ReloadTimerHandle;
	
	//RELOADING
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AK 47")
	float ReloadLength;
	
	//RELOADING
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Reloading")
	bool bReloading;

	UFUNCTION(BlueprintCallable, Category = "AK47")
	void SpawnAK47();

	//MAG ATTACH
	AC_AK47Mag* AK47Mag;

	//MAG ATTACH
	UFUNCTION(BlueprintCallable, Category = "SpawnMagOnPlayer")
	void SpawnMagOnPlayersBack(TSubclassOf<AC_AK47Mag>AK47MagClass);

	//MAG ATTACH
	FName MagPlayersBackAttachSocketName;
	
	//MAG ATTACH
	FName MagPlayersHandAttachSocketName;

	//KABUTO ATTACH
	UFUNCTION(BlueprintCallable, Category = "SpawnKabuto")
	void SpawnKabuto(TSubclassOf<AC_Kabuto>KabutoClass);

	//KABUTO ATTACH
	AC_Kabuto* Kabuto;

	//KABUTO ATTACH
	FName KabutoAttachSocketName;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//DOUBLEJUMP-> The declaration of the function that handles double jumping
	UFUNCTION()
	void DoubleJump();
	
	//DOUBLEJUMP-> The declaration of the variable that will track the number of jumps
	UPROPERTY(EditAnywhere, Category = "DoubleJump")
	int DoubleJumpCounter;

	//DOUBLEJUMP-> he declaration of the variable that determine how high the player can jump
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DoubleJump")
	float JumpHeight;

	//SPRINT-> The declaration of the sprint function
	UFUNCTION(BlueprintCallable)
	void Sprint();

	//SPRINT-> The declaration of the stopsprint function
	UFUNCTION(BlueprintCallable)
	void StopSprinting();

	//SPRINT-> The declaration of the defaultspeed variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float Defaultspeed;

	//SPRINT-> The declaration of the sprintspeed variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float Sprintspeed;

	//SPRINT-> The declaration of the sprintdrain variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float SprintDrain;
	
	//SPRINT-> The declaration of the is sprinting variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprinting")
	bool bIsSprinting;

	//DASH-> The declaration of the DASH function
	UFUNCTION()
	void Dash();

	//DASH-> The declaration of the DASH distance variable
	UPROPERTY(EditAnywhere)
	float DashDistance;
	
	//DASH-> The declaration of the DASH cooldown variable
	UPROPERTY(EditAnywhere)
	float DashCoolDown;
	
	//DASH-> the amount of stamina that will be taken away
	float DashDrain;
	
	//DASH-> The declaration of the DASH stop variable
	UPROPERTY(EditAnywhere)
	float DashStop;
	
	//DASH-> The declaration of the bCanDash variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "dash")
	bool bCanDash;

	//DASH-> The declaration of the stopdashing function
	UFUNCTION()
	void StopDashing();

	//DASH-> The declaration of the Resetdashing function
	UFUNCTION()
	void ResetDashing();

	//DASH-> The declaration of the UnUsedHandle variable
	// timers are the equivelent to a delay in blueprints
	UPROPERTY()
	FTimerHandle UnUsedHandle;

	//JUMP-> functions 

	void jumponce();
	
	void stopjumponce();

	FTimerHandle JumpTimer;

	FTimerHandle TimeBetweenJumps;

	//TwoButtonsPressedForSprint

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	bool bSprintStartStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	bool bSprintResetStatus;

	FTimerHandle TimeForSprintResetStatus;

	FTimerHandle TimeForSprintStartStatus;

	UFUNCTION(BLueprintCallable)
	void ResetSprintPressed();

	UFUNCTION(BlueprintCallable)
	void ResetSprintReleased();

	UFUNCTION(BlueprintCallable)
	void ResetSprintCheckStatus();

	UFUNCTION(BlueprintCallable)
	void StartSprintCheckStatus();

	// STAMINA-> The max stamina variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float MaxStamina;

	//TEST CODE

	//LINETRACE-> will allow the line trace to come from the player camera properly
	virtual FVector GetPawnViewLocation() const override;

	//FIRE
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StartFire();

	void StopFire();

	//STAMINA
	void AddResources();
	
	//AMMO-> The function that subtracts ammo
	UFUNCTION()
	void SubtractAmmo();

	UFUNCTION()
	void CanFire();

private:
	class UAIPerceptionStimuliSourceComponent* Stimulus;

	UFUNCTION()
	void SetupStimulus();
};
