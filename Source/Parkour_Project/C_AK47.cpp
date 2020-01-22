// Fill out your copyright notice in the Description page of Project Settings.


#include "C_AK47.h"

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
	
}

// Called every frame
void AC_AK47::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

