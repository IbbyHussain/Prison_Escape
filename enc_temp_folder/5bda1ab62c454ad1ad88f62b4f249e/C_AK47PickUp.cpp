// Fill out your copyright notice in the Description page of Project Settings.


#include "C_AK47PickUp.h"
#include "Components/BoxComponent.h"

// Sets default values
AC_AK47PickUp::AC_AK47PickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetRelativeScale3D(FVector(12.0f, 7.0f, 5.0f));
	BoxComponent->SetRelativeLocation(FVector(70.0f,0.0f,70.0f));
	BoxComponent->AttachTo(RootComponent);

	SetActorScale3D(FVector(0.15));
}

// Called when the game starts or when spawned
void AC_AK47PickUp::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AC_AK47PickUp::OnOverlapBegin);
	
}

void AC_AK47PickUp::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Overlapped"));
	Destroy();
}

// Called every frame
void AC_AK47PickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MeshComponent->SetSimulatePhysics(true);
}

