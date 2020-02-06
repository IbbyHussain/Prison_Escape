// Fill out your copyright notice in the Description page of Project Settings.


#include "C_HealthComponent.h"

// Sets default values for this component's properties
UC_HealthComponent::UC_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	DefaultHealth = 100;
}


// Called when the game starts
void UC_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* MyOwner = GetOwner();
	if(MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UC_HealthComponent::TakeAnyDamage);
	}

	Health = DefaultHealth;
}


void UC_HealthComponent::TakeAnyDamage(AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if(Damage <= 0.0f)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);

}

// Called every frame
void UC_HealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

