// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Samurai.h"
#include "AI_Samurai_Guard_Weapon.h"
#include "AI_Samurai_Guard_WeaponCase.h"
#include "Runtime/Engine/Classes/Engine/World.h."

// Sets default values
AAI_Samurai::AAI_Samurai()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ANIMATION -> Assigning the hip socket 
	WeaponAttachSocketName = "WeaponSocket";
	
	//ANIMATION -> Assigning the right hand socket
	WeaponAttachSocket = "WeaponSwordSocket";

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

// Called every frame
void AAI_Samurai::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAI_Samurai::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

