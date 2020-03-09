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
#include "C_AK47.h"
#include "Components/CapsuleComponent.h"
#include "C_AK47Mag.h"
#include "C_Kabuto.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "C_HealthComponent.h"
#include "AI_Samurai_Guard_Weapon.h"



//CONSTRUCTOR-> Sets default values
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
	DashDistance = 12000;

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

	//ZOOM->
	ZoomedFOV = 60.0f;

	//ZOOM->
	ZoomInterpSpeed = 20.0f;

	//FIRING->
	WeaponAttachSocketName = "RifleSocket";

	//AMMO
	LoadedAmmo = 30;

	//AMMO
	MaxAmmo = 30;
	
	//RELOADING
	ReloadLength = 2.16f;

	//RELOADING
	bReloading = false;

	//MAG ATTACH
	MagPlayersBackAttachSocketName = "MagAttachSocketBack";

	MagPlayersHandAttachSocketName = "MagAttachSocketHand";

	KabutoAttachSocketName = "KabutoSocket";

	SetupStimulus();

	//AI DAMAGE
	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(55.f, 96.0f);;
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UC_HealthComponent>("HealthComponent");

	bPlayerHasDied = false;

	bHasBeenDamaged = false;
}

// EVENT BEGIN PLAY-> Called when the game starts or when spawned
void APlayer_Character::BeginPlay()
{
	Super::BeginPlay();

	//ZOOM->
	DefaultFOV = CameraComp->FieldOfView;

	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &APlayer_Character::OnOverlapBegin);

	HealthComponent->OnHealthChanged.AddDynamic(this, &APlayer_Character::OnHealthUpdated);
}

//Spawns AK47
void APlayer_Character::SpawnAK47()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AK47 = GetWorld()->SpawnActor<AC_AK47>(AK47Class, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

	if (AK47)
	{
		AK47->SetOwner(this);
		AK47->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponAttachSocketName);
	}
}

//MAG ATTACH-> Spawns mag on players back
void APlayer_Character::SpawnMagOnPlayersBack(TSubclassOf<AC_AK47Mag> AK47MagClass)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	AK47Mag = GetWorld()->SpawnActor<AC_AK47Mag>(AK47MagClass, FVector::ZeroVector, FRotator::ZeroRotator);
	AK47Mag->SetOwner(this);
	AK47Mag->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, MagPlayersBackAttachSocketName);

	AK47Mag = GetWorld()->SpawnActor<AC_AK47Mag>(AK47MagClass, FVector::ZeroVector, FRotator::ZeroRotator);
	AK47Mag->SetOwner(this);
	AK47Mag->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, MagPlayersHandAttachSocketName);
}

//SPWAN KABUTO
void APlayer_Character::SpawnKabuto(TSubclassOf<AC_Kabuto> KabutoClass)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Kabuto = GetWorld()->SpawnActor<AC_Kabuto>(KabutoClass, FVector::ZeroVector, FRotator::ZeroRotator);
	Kabuto->SetOwner(this);
	Kabuto->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, KabutoAttachSocketName);

}

//AI DAMAGE-> any overlap event causes damage
void APlayer_Character::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp && !bHasBeenDamaged)
	{
		UGameplayStatics::ApplyDamage(this, 10.0f, OtherActor->GetInstigatorController(), OtherActor, DefaultDamage);
		bHasBeenDamaged = true;
	}
}

//PLAYERDEATH
void APlayer_Character::PlayerDeath()
{
	UE_LOG(LogTemp, Log, TEXT("Called death function"))
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();
	GetMesh()->SetSimulatePhysics(true);
	bPlayerHasDied = true;
	Playwidget = true;
	bReloading = true;
	//AK47->bCanFire = false;	
}

//UPDATES HEALTH
void APlayer_Character::OnHealthUpdated(UC_HealthComponent * HealthComponent, float Health, float HealthDelta, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (Health <= 0.0f)
	{
		PlayerDeath();
		UE_LOG(LogTemp, Log, TEXT("Died"));
		
	}
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
		if (MaxStamina >= 0)
		{
			// subtract a value each tick
			MaxStamina -= SprintDrain;
		}

		//if the stamina is leass than or equal to 0
		if (MaxStamina <= 0)
		{
			//call function stop sprinting so the player cant sprint anymore
			StopSprinting();
		}
	}
	
	
	//ZOOM-> will set currentFOV based on the value of bCanZoomIn (left to right)
	float TargetFOV = bCanZoomIn ? ZoomedFOV : DefaultFOV;

	float NewFOV = FMath::FInterpTo(CameraComp->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed);

	//ZOOM-> Ensures that the FOV is constantly updated
	CameraComp->SetFieldOfView(NewFOV);

	CanFire();

	//if(bHasBeenDamaged)
	//{

	//	GetWorldTimerManager().SetTimer(DamagedTimerHandle, this, &APlayer_Character::DamageFunction, 1.25f, false);

	//	//UE_LOG(LogTemp, Log, TEXT("Damaged"));
	//	
	//}

}

void APlayer_Character::DamageFunction()
{
	bHasBeenDamaged = false;
	//UE_LOG(LogTemp, Log, TEXT("UNDamaged"));
}

//MOVEMENTCODE->

//BASICMOVEMENT-> The function for moving forward or backwards
void APlayer_Character::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector()* Value);
}

//BASICMOVEMENT-> The function for moving left or right
void APlayer_Character::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector()* Value);
}

//SPRINT-> (pressed) the function for sprinting
void APlayer_Character::Sprint()
{
	//bCanRegenStamina = false;
	bSprintStartStatus = true;
	//Delay here
	GetWorldTimerManager().SetTimer(TimeForSprintStartStatus, this, &APlayer_Character::StartSprintCheckStatus, DashStop, false);
}

//SPRINT-> checks the sprint status
void APlayer_Character::StartSprintCheckStatus()
{
	// Checks if second button is pressed
	if (!bSprintResetStatus)
	{
		//UE_LOG(LogTemp, Log, TEXT("UE_LOG_START"));
	}

	//if both buttons pressed
	if (bSprintStartStatus && bSprintResetStatus)
	{
		//UE_LOG(LogTemp, Log, TEXT("UE_LOG_BOTHPRESSED"));

		if (MaxStamina >= 0.01 || GetCharacterMovement()->MaxWalkSpeed >= 550)
		{
			//sets the character speed to the sprint speed variable
			GetCharacterMovement()->MaxWalkSpeed = Sprintspeed;
			bIsSprinting = true;
		}
	}
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

//SPRINT RESET->  when button pressed
void APlayer_Character::ResetSprintPressed()
{
	bSprintResetStatus = true;
	GetWorldTimerManager().SetTimer(TimeForSprintResetStatus, this, &APlayer_Character::ResetSprintCheckStatus, DashStop, false);
}

//SPRINT RESET-> when button is released
void APlayer_Character::ResetSprintReleased()
{
	bSprintResetStatus = false;
	StopSprinting();
}

//SPRINT RESET->  resets the sprint status, checks if button 1 is pressed
void APlayer_Character::ResetSprintCheckStatus()
{
	if (!bSprintStartStatus)
	{
		//print statement here
		//UE_LOG(LogTemp, Log, TEXT("UE_LOG_RESET"));
	}
}

//SINGLE JUMP-> the function for jumping once
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

//SINGLE JUMP->
void APlayer_Character::stopjumponce()
{
	// sets the players number of jumps to 0, so they can jump again
	DoubleJumpCounter = 0;
}

//DOUBLEJUMP-> The function that handles double jumping
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

// DOUBLE JUMP->The function that handles landing after double jumping
void APlayer_Character::Landed(const FHitResult & Hit)
{
	// When the player lands on the floor the amount of jumps
	// is set to zero so they can double jump again
	DoubleJumpCounter = 0;
}

//DASH-> The function for the dash mechanic
void APlayer_Character::Dash()
{
	//bCanRegenStamina = false;
	//checking if the player is able to dash
	if (MaxStamina >= 0.2)
	{
		//bCanRegenStamina = false;
		if (bCanDash)
		{
			//bCanRegenStamina = false;
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
				MaxStamina -= DashDrain;
			}
		}
	}
}

//DASH-> The function for the Stopdash mechanic
void APlayer_Character::StopDashing()
{
	//bCanRegenStamina = true;
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
	//bCanRegenStamina = false;
}

//STAMINA
void APlayer_Character::AddResources()
{
	MaxStamina += 0.1;
	
	MaxAmmo += 15;
}

//WEAPON CODE->

//ZOOM-> Initial Zoom
void APlayer_Character::BeginZoom()
{
	if(AK47 && !bIsSprinting && !bPlayerHasDied)
	{
		bCanZoomIn = true;
	}
}

//ZOOM-> End Zoom
void APlayer_Character::EndZoom()
{
	bCanZoomIn = false;
}

//FIRING-> can only fire when ammo is 1 or more
void APlayer_Character::StartFire()
{
	if (AK47 && LoadedAmmo > 0)
	{
		AK47->StartFire();
	}
}

//AMMO->SUBTRACT AMMO FUNCTION
void APlayer_Character::SubtractAmmo()
{
	if (LoadedAmmo <= 0)
	{
		AK47->StopFire();
		return;
	}
	LoadedAmmo -= 1;
}

//FIRING
void APlayer_Character::CanFire()
{
	
	if(AK47)
	{
		AK47->bCanFire = true;

		if (bIsSprinting || bReloading)
		{
			AK47->bCanFire = false;
		}
	}
}

//AI STIMULUS
void APlayer_Character::SetupStimulus()
{
	Stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	Stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	Stimulus->RegisterWithPerceptionSystem();

}

//RELOADING
void APlayer_Character::ReloadDuration()
{
	if(!bReloading)
	{
		if (MaxAmmo <= 0 || LoadedAmmo >= 30)
		{
			return;
		
		}
		else
		{
			
			GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &APlayer_Character::Reload, ReloadLength, false);

		}
		bReloading = true;
	}
}

//RELOADING
void APlayer_Character::Reload()
{
	if(MaxAmmo < (30 - LoadedAmmo))
	{
		LoadedAmmo = LoadedAmmo + MaxAmmo;
		MaxAmmo = 0;
	}
	else
	{
		MaxAmmo = MaxAmmo - (30 - LoadedAmmo);
		LoadedAmmo = 30;
	}

	bReloading = false;
}

//STOP FIRING
void APlayer_Character::StopFire()
{
	if (AK47)
	{
		AK47->StopFire();
	}
}

//LINETRACE-> allows the line trace to come from the camera
FVector APlayer_Character::GetPawnViewLocation() const
{
	// null check
	if (CameraComp) 
	{
		//returns the camera location
		return CameraComp->GetComponentLocation();
	}

	// other wise returns pawn location
	return Super::GetPawnViewLocation();
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

	//JUMP->
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayer_Character::jumponce);

	//ZOOM->
	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &APlayer_Character::BeginZoom);

	//ZOOM->
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &APlayer_Character::EndZoom);

	//FIRE
	PlayerInputComponent->BindAction("SemiFire", IE_Pressed, this, &APlayer_Character::StartFire);
	PlayerInputComponent->BindAction("SemiFire", IE_Released, this, &APlayer_Character::StopFire);

	//AMMO->
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayer_Character::ReloadDuration);
}



	

