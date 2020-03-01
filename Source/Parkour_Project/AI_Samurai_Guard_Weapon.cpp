// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Samurai_Guard_Weapon.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h."
#include "Components/BoxComponent.h"
#include "AI_Samurai.h"

// Sets default values
AAI_Samurai_Guard_Weapon::AAI_Samurai_Guard_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Weaponref = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	RootComponent = Weaponref;

	//sets the transform of the collision box
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxComponent->SetRelativeScale3D(FVector(55.0f, 10.0f, 10.0f));
	BoxComponent->SetRelativeLocation(FVector(1500.0f, 10.0f, 10.0f));
	BoxComponent->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AAI_Samurai_Guard_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
	// overlap 
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AAI_Samurai_Guard_Weapon::OnOverlapBegin);

	TSubclassOf<AAI_Samurai> ClassToFind;
	ClassToFind = AAI_Samurai::StaticClass();
	TArray<AActor*> FoundClass;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoundClass);
}


//test
void AAI_Samurai_Guard_Weapon::test()
{
	UE_LOG(LogTemp, Log, TEXT("Successful cast"));
	Weaponref->SetSimulatePhysics(true);
	
	//Weaponref->DetachFromActor();

}

//OVERLAP
void AAI_Samurai_Guard_Weapon::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherActor == PlayerCharacterReference)
	{
		UE_LOG(LogTemp, Log, TEXT("OVERLAPPED"));
	}

	
}

// Called every frame
void AAI_Samurai_Guard_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

