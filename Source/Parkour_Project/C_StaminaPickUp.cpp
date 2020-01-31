// Fill out your copyright notice in the Description page of Project Settings.


#include "C_StaminaPickUp.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Math/Vector.h"

// Sets default values
AC_StaminaPickUp::AC_StaminaPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaminaPickupSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComp");

	StaminaPickupEffect = CreateDefaultSubobject<UParticleSystemComponent>("Particlecomp");

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	
	RootComponent = StaminaPickupSkeletalMesh;
	BoxComponent->AttachTo(RootComponent);
	StaminaPickupEffect->AttachTo(RootComponent);

	Self->StaminaPickupSkeletalMesh;
	
	/*FVector StaminaPickupScale(20.f);
	Self->SetActorRelativeScale3D(StaminaPickupScale);*/

	//Scales all components to 2
	SetActorScale3D(FVector(1.5f));

	//changes the relative scale of the box collision
	BoxComponent->SetRelativeScale3D(FVector(0.65f));
	BoxComponent->SetRelativeLocation(FVector(0.f, 0.f, 11.f));

	//Physics
	StaminaPickupSkeletalMesh->SetSimulatePhysics = true;
}

// EVENTBEGINPLAY-> Called when the game starts or when spawned
void AC_StaminaPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// EVENT TICK-> Called every frame
void AC_StaminaPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

