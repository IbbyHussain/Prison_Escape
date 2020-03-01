// Fill out your copyright notice in the Description page of Project Settings.


#include "C_AK47.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Parkour_Project.h"
#include "TimerManager.h"
#include "Player_Character.h"
#include "C_AK47Mag.h"
#include "GameFramework/Pawn.h"



// Sets default values
AC_AK47::AC_AK47()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AK47Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");
	RootComponent = AK47Mesh;

	MuzzleSocket = "MuzzleSocket";

	TracerTargetName = "Target";

	BaseDamage = 20.0f;

	FireRate = 300;

	MagAttachSocket = "MagSocket";

	bCanFire = true;

	bISFiring = false;
}

// Called when the game starts or when spawned
void AC_AK47::BeginPlay()
{
	Super::BeginPlay();

	TimeBetweenShots = 60 / FireRate;

	//cast to player
	PlayerCharacterRef = Cast<APlayer_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

//FIRE-> The firing function for the AK47
void AC_AK47::Fire()
{
	if (bCanFire)
	{
		// sets the player as owner of this weapon
		AActor* MyOwner = GetOwner();
		// checks so that it will not run if null
		if (MyOwner)
		{
			if (PlayerCharacterRef)
			{
				PlayerCharacterRef->SubtractAmmo();
			}

			// vector values for line trace parameters
			FVector EyeLocation;
			FRotator EyeRotation;
			//Gets the point of the camera
			MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

			FVector ShotDirection = EyeRotation.Vector();

			// The line trace will end from camera to 1000units in the direction of camera
			FVector TraceEnd = EyeLocation + (ShotDirection * 5000);

			// ignores the player and the gun so they dont take damage
			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(MyOwner);
			QueryParams.AddIgnoredActor(this);
			//complex line trace
			QueryParams.bTraceComplex = true;
			QueryParams.bReturnPhysicalMaterial = true;


			// the "target" for the tracer particle parameter
			FVector TracerEndPoint = TraceEnd;
			
			FHitResult Hit;
			if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
			{
				AActor* HitActor = Hit.GetActor();
				EPhysicalSurface SurfaceType = UPhysicalMaterial::DetermineSurfaceType(Hit.PhysMaterial.Get());

				float ActualDamage = BaseDamage;
				if (SurfaceType == SURFACE_FLESHVULNERABLE)
				{
					ActualDamage *= 2.0f;
				}

				//Damage
				UGameplayStatics::ApplyPointDamage(HitActor, ActualDamage, ShotDirection, Hit, MyOwner->GetInstigatorController(), this, DefaultDamage);

				//PHYSMAterial Logic
				UParticleSystem* SelectedImpactEffect = nullptr;
				switch (SurfaceType)
				{
				case SURFACE_FLESHDEFAULT:
				case SURFACE_FLESHVULNERABLE:
					SelectedImpactEffect = FleshImpactEffect;
					break;
				default:
					SelectedImpactEffect = DefaultImpactEffect;
					break;
				}

				TracerEndPoint = Hit.ImpactPoint;

				// will play the impact effect that has been chosen by switch statement
				if (SelectedImpactEffect)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SelectedImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
				}
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

			//Debug Line for line trace
			//DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Green, false, 1.0f, 0, 1.0f);

			APawn* MyOwner = Cast<APawn>(GetOwner());
			if (MyOwner)
			{
				APlayerController* PlayerController = Cast<APlayerController>(MyOwner->GetController());
				//get controller
				if (PlayerController)
				{
					PlayerController->ClientPlayCameraShake(FireCameraShake);
				}

			}

			// gets the time in the world
			LastFireTime = GetWorld()->TimeSeconds;


		}
	}
}

//FIRING->
void AC_AK47::StartFire()
{
	float FirstDelay = FMath::Max(LastFireTime + TimeBetweenShots - GetWorld()->TimeSeconds, 0.0f);

	GetWorldTimerManager().SetTimer(FiringTimer, this, &AC_AK47::Fire, TimeBetweenShots, true, FirstDelay);

	bISFiring = true;
	

}

//FIRING->
void AC_AK47::StopFire()
{
	GetWorldTimerManager().ClearTimer(FiringTimer);

	bISFiring = false;

}

//MAG->spawns mag attached to weapon
void AC_AK47::SpawnMag(TSubclassOf<AC_AK47Mag> MagClass)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	MagRef = GetWorld()->SpawnActor<AC_AK47Mag>(MagClass, FVector::ZeroVector, FRotator::ZeroRotator);
	MagRef->SetOwner(this);
	MagRef->AttachToComponent(AK47Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, MagAttachSocket);
}

//EVENT TICK-> Called every frame
void AC_AK47::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

