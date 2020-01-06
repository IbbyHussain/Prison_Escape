// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Samurai_Guard_Weapon.h"

// Sets default values
AAI_Samurai_Guard_Weapon::AAI_Samurai_Guard_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Weaponref = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	
	
}

// Called when the game starts or when spawned
void AAI_Samurai_Guard_Weapon::BeginPlay()
{
	Super::BeginPlay();
	//SetActorRelativeScale3D(FVector(1.0f, 0, 1.f));
}

// Called every frame
void AAI_Samurai_Guard_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

