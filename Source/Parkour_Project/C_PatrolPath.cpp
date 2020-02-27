// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PatrolPath.h"

// Sets default values
AC_PatrolPath::AC_PatrolPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

FVector AC_PatrolPath::get_patrol_point(int const index) const
{
	return patrol_points[index];
}

int AC_PatrolPath::num() const
{
	return patrol_points.Num();
}
