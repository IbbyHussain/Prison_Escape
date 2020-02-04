// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Samurai.h"
#include "AI_Samurai_Guard_Weapon.h"
#include "AI_Samurai_Guard_WeaponCase.h"
#include "GameFramework/MovementComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h."
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Components/MeshComponent.h"
#include "C_StaminaPickUp.h"



// Sets default values
AAI_Samurai::AAI_Samurai()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ANIMATION -> Assigning the hip socket 
	WeaponAttachSocketName = "WeaponSocket";
	
	//ANIMATION -> Assigning the right hand socket
	WeaponAttachSocket = "WeaponSwordSocket";

	Health = 1;

	DeathTimer = 10.0f;
	
	Black = CreateDefaultSubobject<UMaterial>("Black");

	StaminaPickupAttachSocket = "StaminaPickupSpawn";
	

}

// Called when the game starts or when spawned
void AAI_Samurai::BeginPlay()
{
	Super::BeginPlay();

	

}

// WEAPON -> The function that spawns the samurai weapon
void AAI_Samurai::SpawnWeapon(TSubclassOf<AAI_Samurai_Guard_Weapon> SamuraiWeaponClass)
{
	FActorSpawnParameters SpawnParams; 
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	SamuraiWeapon = GetWorld()->SpawnActor<AAI_Samurai_Guard_Weapon>(SamuraiWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator); 
	SamuraiWeapon->SetOwner(this); 
	SamuraiWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponAttachSocket);
}

// WEAPON -> The function that spawns the samurai weapon case
void AAI_Samurai::SpawnWeaponCase(TSubclassOf<AAI_Samurai_Guard_WeaponCase> SamuraiWeaponCaseClass)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SamuraiWeaponCase = GetWorld()->SpawnActor<AAI_Samurai_Guard_WeaponCase>(SamuraiWeaponCaseClass, FVector::ZeroVector, FRotator::ZeroRotator);
	SamuraiWeaponCase->SetOwner(this);
	SamuraiWeaponCase->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponAttachSocketName);
}

//DEATH->
void AAI_Samurai::Death()
{
	UE_LOG(LogTemp, Log, TEXT("ruuning death function"));
	//simulates physics
	GetMesh()->SetSimulatePhysics(true);
	//Stops character movement
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();
	// Timer used with function that contain parameters
	FTimerHandle UniqueHandle;
	FTimerDelegate RespawnDelegate = FTimerDelegate::CreateUObject(this, &AAI_Samurai::DespawnAI);
	GetWorldTimerManager().SetTimer(UniqueHandle, RespawnDelegate, DeathTimer, false);
	//Changes colour of mesh
	GetMesh()->SetMaterial(4, Black);
	GetMesh()->SetMaterial(9, Black);
	GetMesh()->SetMaterial(13, Black);
	GetMesh()->SetMaterial(18, Black);
	GetMesh()->SetMaterial(19, Black);
	//Spawns stamina core
	

}

void AAI_Samurai::DespawnAI()
{
	UE_LOG(LogTemp, Log, TEXT("Despawn body"));
	Destroy();
	Destroy(SamuraiWeaponCase);
}

//SPAWNING PICKUP->spawns the stamina pickup
void AAI_Samurai::SpawnStaminaPickup(TSubclassOf<AC_StaminaPickUp> StaminaPickupClass)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	StaminaPickupRef = GetWorld()->SpawnActor<AC_StaminaPickUp>(StaminaPickupClass, FVector::ZeroVector, FRotator::ZeroRotator);
	StaminaPickupRef->SetOwner(this);
	StaminaPickupRef->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, StaminaPickupAttachSocket);

}

// Called every frame
void AAI_Samurai::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Health <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("AI has died"));
		Death();
	}
}

// Called to bind functionality to input
void AAI_Samurai::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

