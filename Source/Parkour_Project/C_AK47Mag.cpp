// Fill out your copyright notice in the Description page of Project Settings.


#include "C_AK47Mag.h"

// Sets default values
AC_AK47Mag::AC_AK47Mag()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComponent");

}

// Called when the game starts or when spawned
void AC_AK47Mag::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AC_AK47Mag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

