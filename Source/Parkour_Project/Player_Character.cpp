// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Controller.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "TimerManager.h"



// Sets default values
APlayer_Character::APlayer_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//CAMERA-> creation of the spring arm
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArm");

	//CAMERA-> the spring arm will uss pawn conttrol rotation
	SpringArmComp->bUsePawnControlRotation = true;

	//CAMERA-> attaches the spring arm to the root
	SpringArmComp->SetupAttachment(RootComponent);
	
	//CAMERA-> creation of the camera
	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
	
	//CAMERA-> creation of the camera
	CameraComp->SetupAttachment(SpringArmComp);

	//CAMERA-> Attaches the spring arm to the characters mesh as well as the characters skeleton
	// via the socket "HeadSocket" -> gives a good fps look
	SpringArmComp->SetupAttachment(GetMesh(), "HeadSocket");
	
	// DOUBLEJUMP-> Sets the value of the jump height
	JumpHeight = 580.0f; // set to 600 for more fluid jump
	
	//SPRINT-> The default speed of the character
	Defaultspeed = 550.0f;
	
	//SPRINT-> How fast the character should be when sprinting
	Sprintspeed = 1200.0f;

	//DASH-> the boolean that controlls wether the player can dash or not
	bCanDash = true;

	//DASH-> The distance the player will dash
	DashDistance = 6000;

	//DASH-> 1 second cooldown for dashing
	DashCoolDown = 1.0f;

	//DASH->
	DashStop = 0.1f;

	//JUMP-> checks to see if the player can jump, used in the animation blueprint
	bCanJump = true;

	// Time used between the delay of each jump
	JumpAnimationTime = 1.1f; // set to 1 for more fluid jump

	//JUMP->counts the number of jumps the player has done
	DoubleJumpCounter = 0;

	//SPRINT-> Checks to see if the player is sprinting
	bIsSprinting = false;

	//DASH-> Sets the default value of the biscurrentlydashing variable to fasle
	//bIsCurrentlyDashing = false;

	//STAMINA-> sets the value of the players stamina
	MaxStamina = 1.0f;

	//SPRINT-> The amount of stamina that is taken from the players total stamina when sprinting
	SprintDrain = 0.001f;

	//DASH-> The amount of stamina that is taken from the players total stamina when dashing
	DashDrain = 0.2;

	//TEST CODE
	bSprintStartStatus = false;

	bSprintResetStatus = false;
}

// EVENT BEGIN PLAY-> Called when the game starts or when spawned
void APlayer_Character::BeginPlay()
{
	Super::BeginPlay();


	
}

// EVENT TICK-> Called every frame
void APlayer_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//SPRINT-> STAMINA DRAIN If the player is sprinting
	// drains over time
	if (bIsSprinting)
	{
		// if the stamina is greater than or equal to 0
		if(MaxStamina >= 0)
		{
			// subtract a value each tick
			MaxStamina = MaxStamina - SprintDrain;
		}

	    //if the stamina is leass than or equal to 0
		if (MaxStamina <= 0)
		{
			//call function stop sprinting so the player cant sprint anymore
		StopSprinting();
		}
	}
	
	

}

//MOVEMENT-> The function for moving forward or backwards
void APlayer_Character::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector()* Value);
}

//MOVEMENT-> The function for moving left or right
void APlayer_Character::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector()* Value);
}

//JUMP-> the function for jumping once
void APlayer_Character::jumponce()
{
	// if the player has not jumped, they can jump
	if (DoubleJumpCounter == 0)
	{
		GetCharacterMovement()->AirControl = 1.0f;
		APlayer_Character::LaunchCharacter(FVector(0, 0, JumpHeight), false, true);
		DoubleJumpCounter++;
	}
}

void APlayer_Character::stopjumponce()
{
	// sets the players number of jumps to 0, so they can jump again
	DoubleJumpCounter = 0;
}

//SPRINT-> when button pressed
void APlayer_Character::ResetSprintPressed()
{
	bSprintResetStatus = true;
	GetWorldTimerManager().SetTimer(TimeForSprintResetStatus, this, &APlayer_Character::ResetSprintCheckStatus, DashStop, false);
}

//SPRINT-> when button is released
void APlayer_Character::ResetSprintReleased()
{
	bSprintResetStatus = false;
	StopSprinting();
}

//SPRINT-> resets the sprint status, checks if button 1 is pressed
void APlayer_Character::ResetSprintCheckStatus()
{
	if(!bSprintStartStatus)
	{
		//print statement here
		UE_LOG(LogTemp, Log, TEXT("UE_LOG_RESET"));
	
	}
}

// DOUBLEJUMP-> The function that handles double jumping
void APlayer_Character::DoubleJump()
{
	// a check to see if the character can double jump, as they should be able to
	// if they have already jumped twice
	// if the player has jumped once or hasnt jumped at all
	if (DoubleJumpCounter <= 1)
	{
		// launches the character in the z direction(UP) via the jump height variable.
		APlayer_Character::LaunchCharacter(FVector(0, 0, JumpHeight), false, true);
		// allows the character to have better air control whilst jumping
		GetCharacterMovement()->AirControl = 1.0f;
		// Increments the double jump counter so that the player
		// cannot jump an infinate amount of times
		// can jump only twice
		DoubleJumpCounter++;
	}
}

// DOUBLEJUMP->The function that handles landing after double jumping
void APlayer_Character::Landed(const FHitResult & Hit)
{
	// When the player lands on the floor the amount of jumps
	// is set to zero so they can double jump again
	DoubleJumpCounter = 0;
}

//SPRINT-> PRESSED the function for sprinting
void APlayer_Character::Sprint()
{
	bSprintStartStatus = true;
	//Delay here
	GetWorldTimerManager().SetTimer(TimeForSprintStartStatus, this, &APlayer_Character::StartSprintCheckStatus,DashStop,false);
}

//SPRINT-> RELEASED the function for stop sprinting
void APlayer_Character::StopSprinting()
{
	//TEST CODE
	bSprintStartStatus = false;
	//sets the character speed to the default speed variable
	GetCharacterMovement()->MaxWalkSpeed = Defaultspeed;
	bIsSprinting = false;
}

//SPRINT->
void APlayer_Character::StartSprintCheckStatus()
{
	// Checks if second button is pressed
	if(!bSprintResetStatus)
	{
		UE_LOG(LogTemp, Log, TEXT("UE_LOG_START"));
	}
	
	//if both buttons pressed
	if(bSprintStartStatus && bSprintResetStatus)
	{
		UE_LOG(LogTemp, Log, TEXT("UE_LOG_BOTHPRESSED"));
		
		if (MaxStamina >= 0.01 || GetCharacterMovement()->MaxWalkSpeed >= 550)
		{
			//sets the character speed to the sprint speed variable
			GetCharacterMovement()->MaxWalkSpeed = Sprintspeed;
			bIsSprinting = true;

		}
	}

}

//DASH-> The function for the dash mechanic
void APlayer_Character::Dash()
{
	//checking if the player is able to dash
	if (MaxStamina >= 0.2) 
	{
		if (bCanDash)
		{
			// stops the character from being slowed down by obstacles
			GetCharacterMovement()->BrakingFrictionFactor = 0.f;
			// Allows thge player to only dash along the x or y axis but no z, 
			//as we dont want them dashing up or down
			// send them the distance of dash distance variable
			LaunchCharacter(FVector(CameraComp->GetForwardVector().X, CameraComp->GetForwardVector().Y, 0).GetSafeNormal()* DashDistance, true, true);
			// stops player from dashing again
			bCanDash = false;
			// after 0.1 seconds calls the stop dashing function
			GetWorldTimerManager().SetTimer(UnUsedHandle, this, &APlayer_Character::StopDashing, DashStop, false);
			// subtracts stamina if the player is dashing
			if (MaxStamina >= 0)
			{
				MaxStamina = MaxStamina - DashDrain;
			}
		}
	}
}

//DASH-> The function for the Stopdash mechanic
void APlayer_Character::StopDashing()
{
	
	// stops the player from moving
	GetCharacterMovement()->StopMovementImmediately();
	// sets thefriction back to default
	GetCharacterMovement()->BrakingFrictionFactor = 2.f;
	// the delay between reseting each dash
	GetWorldTimerManager().SetTimer(UnUsedHandle, this, &APlayer_Character::ResetDashing, DashCoolDown, false);
}

//DASH-> The function for the Resetdash mechanic
void APlayer_Character::ResetDashing()
{
	// allows the player to dash after cooldown
	bCanDash = true;
}

// Called to bind functionality to input
void APlayer_Character::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//MOVEMENT-> Binding the axis for moving foward or backward, so it can be called in game
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayer_Character::MoveForward);
	
	//MOVEMENT-> Binding the axis for moving left or right, so it can be called in game
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayer_Character::MoveRight);
	
	//LOOKING-> Binds the axis for lokking up or down
	PlayerInputComponent->BindAxis("LookUp", this, &APlayer_Character::AddControllerPitchInput);

	//LOOKING-> Binds the axis for lokking left or right
	PlayerInputComponent->BindAxis("LookRight", this, &APlayer_Character::AddControllerYawInput);

	//JUMP-> Binds the axis for jumping
	PlayerInputComponent->BindAction("DoubleJump", IE_Pressed, this, &APlayer_Character::DoubleJump);

	//SPRINT-> Binds the action for sprinting
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayer_Character::Sprint);
	
	//SPRINT-> Binds the action for stop sprinting
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayer_Character::StopSprinting);

	//RESETSPRINT->
	PlayerInputComponent->BindAction("ResetSprint", IE_Pressed, this, &APlayer_Character::ResetSprintPressed);

	//RESETSPRINT->
	PlayerInputComponent->BindAction("ResetSprint", IE_Released, this, &APlayer_Character::ResetSprintReleased);

	//DASH-> binds action for dashing
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &APlayer_Character::Dash);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayer_Character::jumponce);
}



	

