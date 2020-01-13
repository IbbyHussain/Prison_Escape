// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Character_Controller.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

// SETS THE DEFAULT VALUES
AAI_Character_Controller::AAI_Character_Controller()
{
	PrimaryActorTick.bCanEverTick = true;

	//creates the components for the class
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent"));

	//sets values for variables
	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILooseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldofView;
	SightConfig->SetMaxAge(AISightAge);

	// setting the affliation variables to true
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	//chnaging values for perception
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AAI_Character_Controller::OnPawnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

//EVENT BEGINPLAY
void AAI_Character_Controller::BeginPlay()
{
	Super::BeginPlay();

	if(GetPerceptionComponent() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ALL SYSETMS READY NIGGAAA"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("theres a problem CEACKERRRRRRR"));
	}

}

// EVENT POSSESS 
void AAI_Character_Controller::OnPossess(APawn * Pawn)
{
	Super::OnPossess(Pawn);
}

void AAI_Character_Controller::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

FRotator AAI_Character_Controller::GetControlRotation() const
{
	if(GetPawn() == nullptr)
	{
		return FRotator(0.0f,0.0f,0.0f);
	}

	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void AAI_Character_Controller::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
}


