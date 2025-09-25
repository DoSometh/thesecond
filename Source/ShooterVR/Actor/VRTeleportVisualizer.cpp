// Fill out your copyright notice in the Description page of Project Settings.

#include "VRTeleportVisualizer.h"
#include "NiagaraComponent.h"

// Sets default values
AVRTeleportVisualizer::AVRTeleportVisualizer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	VRTeleportVisualizerRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRTeleportVisualizerRoot"));
	RootComponent = VRTeleportVisualizerRoot;

	//Bounds
	NSPlayAreaBounds = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NSPlayAreaBounds"));
	NSPlayAreaBounds->SetupAttachment(RootComponent);

	NSTeleportRing = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NSTeleportRing"));
	NSTeleportRing->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AVRTeleportVisualizer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVRTeleportVisualizer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld() &&
		GetWorld()->GetFirstPlayerController() &&
		GetWorld()->GetFirstPlayerController()->GetPawn() &&
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager)
	{
		FTransform PawnTransform = GetWorld()->GetFirstPlayerController()->GetPawn()->GetTransform();
		FRotator PawnRotator = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();
		FVector CameraLocation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();

		FVector CameraRelativeLocation = PawnTransform.InverseTransformPosition(CameraLocation);

		CameraRelativeLocation *= -1.f;
		CameraRelativeLocation.Z = 0.f;

		NSPlayAreaBounds->SetRelativeLocationAndRotation(CameraRelativeLocation, PawnRotator);
	}	
}

