// Fill out your copyright notice in the Description page of Project Settings.


#include "C_AK47.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AC_AK47::AC_AK47()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AK47Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
	RootComponent = AK47Mesh;

	MuzzleSocket = "MuzzleSocket";

	TracerTargetName = "Target";
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
		
		FVector ShotDirection = EyeRotation.Vector();
		
		// The line trace will end from camera to 1000units in the direction of camera
		FVector TraceEnd = EyeLocation + (ShotDirection * 1000);

		// ignores the player and the gun so they dont take damage
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		//complex line trace
		QueryParams.bTraceComplex = true;

		// the "target" for the tracer particle parameter
		FVector TracerEndPoint = TraceEnd;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
		{
			//Damage

			AActor* HitActor = Hit.GetActor();
			UGameplayStatics::ApplyPointDamage(HitActor, 20.0f, ShotDirection, Hit, MyOwner->GetInstigatorController(), this, DefaultDamage);

			if (ImpactEffect) 
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
			}

			TracerEndPoint = Hit.ImpactPoint;

		}
		
		//Attaches the particle effect to the AK47
		if (MuzzleEffect)
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, AK47Mesh, MuzzleSocket);
		}



		if (TraceEffect)
		{
			//gets the location of the muzzle socket 
			FVector MuzzleLocation = AK47Mesh->GetSocketLocation(MuzzleSocket);

			UParticleSystemComponent* TracerComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TraceEffect, MuzzleLocation);

			if (TracerComp)
			{
				TracerComp->SetVectorParameter(TracerTargetName, TracerEndPoint);
			}

		}

		DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Green, false, 1.0f, 0, 1.0f);

		APawn* MyOwner = Cast<APawn>(GetOwner());
		if(MyOwner)
		{
			APlayerController* PlayerController = Cast<APlayerController>(MyOwner->GetController());
			//get controller
			if(PlayerController)
			{
				PlayerController->ClientPlayCameraShake(FireCameraShake);
			}

		}
	}

}



// Called every frame
void AC_AK47::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

