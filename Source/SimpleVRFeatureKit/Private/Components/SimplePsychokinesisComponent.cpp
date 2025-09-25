// Copyright (C) RenZhai.2025.All Rights Reserved.

#include "Components/SimplePsychokinesisComponent.h"
#include "MotionControllerComponent.h"
#include "SimpleVRFeatureKitLibrary.h"

USimplePsychokinesisComponent::USimplePsychokinesisComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bDoCollisionTest = false;
	bPsychokinesis = false;

	bEnableCameraLag = true;
	bEnableCameraRotationLag = true;
	bUseCameraLagSubstepping = true;

	SubitemComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SubitemComponent"));
	SubitemComponent->SetupAttachment(this);

	CameraLagMaxDistance = 600.f;

	TraceInterval = 0.3f;
	CurrentTraceCount = 0.f;

	SpeedAttraction = 160.f;
	MinimumAttractionDistance = 20.f;
}

void USimplePsychokinesisComponent::SetMotionControllerComponent(UMotionControllerComponent* InMotionControllerComponent)
{
	RefMotionController = InMotionControllerComponent;
}

void USimplePsychokinesisComponent::StartPsychokinesis()
{
	bPsychokinesis = true;
}

void USimplePsychokinesisComponent::UpdateAttractiveForce(float DeltaTime)
{
	TargetArmLength -= DeltaTime * SpeedAttraction;

	TargetArmLength = FMath::Clamp(TargetArmLength, MinimumAttractionDistance, CameraLagMaxDistance);
}

void USimplePsychokinesisComponent::EndPsychokinesis()
{
	bPsychokinesis = false;
}

void USimplePsychokinesisComponent::SetNewGrabComponent(UPrimitiveComponent* InNewComponent)
{
	ControlledComponent = InNewComponent;
}

void USimplePsychokinesisComponent::ResetTargetArmLength()
{
	if (!ControlledComponent.IsValid())
	{
		TargetArmLength = MinimumAttractionDistance;
	}
	else
	{
		TargetArmLength = FVector::Distance(
			ControlledComponent->GetComponentLocation()
			,GetComponentLocation());
	}
}

void USimplePsychokinesisComponent::BeginPlay()
{
	Super::BeginPlay();

	if (SubitemComponent)
	{
		SubitemComponent->SetRelativeLocation(FVector::ZeroVector);
	}
}

void USimplePsychokinesisComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bPsychokinesis)
	{
		if (ControlledComponent.IsValid())
		{
			ControlledComponent->SetWorldLocationAndRotation(
				SubitemComponent->GetComponentLocation(), 
				SubitemComponent->GetComponentRotation());
		}
	}
	else
	{
		CurrentTraceCount += DeltaTime;
		if (CurrentTraceCount > TraceInterval)
		{
			CurrentTraceCount = 0.f;

			//每帧获取一bian
			ControlledComponent = NULL;

			OnPsychokinesisDynamicDelegate.Broadcast(this, CameraLagMaxDistance);

			//开始震动
			if (ControlledComponent.IsValid())
			{
				ResetTargetArmLength();

				if (TouchFeedbackEffect)
				{
					USimpleVRFeatureKitLibrary::PlayHapticEffect(TouchFeedbackEffect, RefMotionController.Get(),1.f);
				}
			}
		}
	}
}

