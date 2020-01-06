// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player_Hakimaru.generated.h"


class UCameraComponent;
class USpringArmComponent;


UCLASS()
class PARKOUR_PROJECT_API APlayer_Hakimaru : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer_Hakimaru();

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

	//SPRINT->
	UFUNCTION()
	void Sprint();

	//SPRINT->
	UFUNCTION()
	void StopSprinting();

	//SPRINT->
	UPROPERTY(EditAnywhere, Category = "Sprint")
	float Defaultspeed;

	//SPRINT->
	UPROPERTY(EditAnywhere, Category = "Sprint")
	float Sprintspeed;

};
