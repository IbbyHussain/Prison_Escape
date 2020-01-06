// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Samurai_Guard_WeaponCase.h"

// Sets default values
AAI_Samurai_Guard_WeaponCase::AAI_Samurai_Guard_WeaponCase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Weaponref = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
}

// Called when the game starts or when spawned
void AAI_Samurai_Guard_WeaponCase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAI_Samurai_Guard_WeaponCase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

