// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;

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

	// STAMINA-> The max stamina variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float MaxStamina;

	// STAMINA-> the current stamina value                                           
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float CurrentStamina;
		

	

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
	UPROPERTY(EditAnywhere, Category = "Sprint")
	float Defaultspeed;

	//SPRINT-> The declaration of the sprintspeed variable
	UPROPERTY(EditAnywhere, Category = "Sprint")
	float Sprintspeed;

	//SPRINT-> The declaration of the sprintdrain variable
	UPROPERTY(EditAnywhere, Category = "Sprint")
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

	//TEST CODE->

	void jumponce();
	void stopjumponce();

	float DashDrain;

	
	FTimerHandle JumpTimer;

	FTimerHandle TimeBetweenJumps;


};
