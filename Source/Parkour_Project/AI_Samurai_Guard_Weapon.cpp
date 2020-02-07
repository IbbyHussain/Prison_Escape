// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Samurai_Guard_Weapon.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h."
#include "AI_Samurai.h"

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

// Called every frame
void AAI_Samurai_Guard_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

