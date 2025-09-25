// Fill out your copyright notice in the Description page of Project Settings.

#include "SimulationModel.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"

ASimulationModel::ASimulationModel()
{
	PrimaryActorTick.bCanEverTick = false;

	SimulationModelRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SimulationModelRoot"));
	RootComponent = SimulationModelRoot;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	ProjectileMovement->MaxSpeed = 400.f;
	ProjectileMovement->InitialSpeed = 400.f;

	Mesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ASimulationModel::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(10.f);
}

// Called every frame
void ASimulationModel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}
