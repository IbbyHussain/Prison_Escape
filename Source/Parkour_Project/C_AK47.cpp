// Fill out your copyright notice in the Description page of Project Settings.


#include "C_AK47.h"
#include "DrawDebugHelpers.h"

// Sets default values
AC_AK47::AC_AK47()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AK47Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
	RootComponent = AK47Mesh;

}

// Called when the game starts or when spawned
void AC_AK47::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_AK47::Fire()
{
	//LineTrace Logic

	// sets the player as owner of this weapon
	AActor* MyOwner = GetOwner();
	// checks so that it will not run if null
	if (MyOwner)
	{
		// vector values for line trace parameters
		FVector EyeLocation;
		FRotator EyeRotation;
		//Gets the point of the camera
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
		// The line trace will end from camera to 1000units in the direction of camera
		FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 1000);

		// ignores the player and the gun so they dont take damage
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		//complex line trace
		QueryParams.bTraceComplex = true;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
		{
			//Damage
		}

		DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Green, false, 1.0f, 0, 1.0f);
	}
}

// Called every frame
void AC_AK47::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

