// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PatrolPoint.h"

// Sets default values
AC_PatrolPoint::AC_PatrolPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_PatrolPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_PatrolPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//GETPATROLPOINTS
FVector AC_PatrolPoint::GetPatrolPoints(int const index) const
{
	//returns the location of the current patrol point
	return PatrolPoints[index];
}

//PATROLPOINTNUM
int AC_PatrolPoint::num() const
{
	// returns the number in the array
	return PatrolPoints.Num();
}

