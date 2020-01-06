// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Hakimaru.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Controller.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"


// Sets default values
APlayer_Hakimaru::APlayer_Hakimaru()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//CAMERA-> creation of the spring arm
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArm");

	//CAMERA->
	SpringArmComp->bUsePawnControlRotation = true;

	//CAMERA->
	SpringArmComp->SetupAttachment(RootComponent);

	//CAMERA-> creation of the camera
	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");

	//CAMERA-> creation of the camera
	CameraComp->SetupAttachment(SpringArmComp);

	//CAMERA-> Attaches the spring arm to the characters mesh as well as the characters skeleton
	// via the socket "HeadSocket" -> gives a good fps look
	SpringArmComp->SetupAttachment(GetMesh(), "HeadSocket");

	// DOUBLEJUMP-> Sets the value of the jump height
	JumpHeight = 600.0f;

	//SPRINT->
	Defaultspeed = 550.0f;

	//SPRINT->
	Sprintspeed = 950.0f;

}

// Called when the game starts or when spawned
void APlayer_Hakimaru::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayer_Hakimaru::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector()* Value);
}

void APlayer_Hakimaru::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector()* Value);
}

void APlayer_Hakimaru::Landed(const FHitResult & Hit)
{
	// When the player lands on the floor the amount of jumps
	// is set to zero so they can double jump again
	DoubleJumpCounter = 0;
}

// Called every frame
void APlayer_Hakimaru::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// DOUBLEJUMP-> The function that handles double jumping
void APlayer_Hakimaru::DoubleJump()
{
	// a check to see if the character can double jump, as thye should be able to
	// if they have already jumped twice
	// if the player has jumped once or hasnt jumped at all
	if (DoubleJumpCounter <= 1)
	{
		// launches the character in the z direction(UP) via the jump height variable.
		APlayer_Hakimaru::LaunchCharacter(FVector(0, 0, JumpHeight), false, true);
		// Increments the double jump counter so that the player
		// cannot jump an infinate amount of times
		// can jump only twice
		DoubleJumpCounter++;
	}
}

void APlayer_Hakimaru::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed = Sprintspeed;
}

void APlayer_Hakimaru::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = Defaultspeed;
}



// Called to bind functionality to input
void APlayer_Hakimaru::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayer_Hakimaru::MoveForward);

	//MOVEMENT-> Binding the axis for moving left or right, so it can be called in game
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayer_Hakimaru::MoveRight);

	//LOOKING-> Binds the axis for lokking up or down
	PlayerInputComponent->BindAxis("LookUp", this, &APlayer_Hakimaru::AddControllerPitchInput);

	//LOOKING-> Binds the axis for lokking left or right
	PlayerInputComponent->BindAxis("LookRight", this, &APlayer_Hakimaru::AddControllerYawInput);

	//JUMP-> Binds the axis for jumping
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayer_Hakimaru::DoubleJump);

	//SPRINT-> Binds the action for sprinting
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayer_Hakimaru::Sprint);

	//SPRINT-> Binds the action for stop sprinting
	PlayerInputComponent->BindAction("Sprnt", IE_Released, this, &APlayer_Hakimaru::StopSprinting);

}

