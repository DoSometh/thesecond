// Copyright (C) RenZhai.2025.All Rights Reserved.

#include "GameFramework/SimpleVRMovementComponent.h"
#include "SimpleVRFeatureKitType.h"

USimpleVRMovementComponent::USimpleVRMovementComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void USimpleVRMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (MovementMode == EMovementMode::MOVE_Custom)
	{
		
	}
}

void USimpleVRMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
	Super::PhysCustom(deltaTime, Iterations);

	if (deltaTime < UCharacterMovementComponent::MIN_TICK_TIME)
	{
		return;
	}

	EVRMovementMode InMode = (EVRMovementMode)CustomMovementMode;

	switch (InMode)
	{
		case EVRMovementMode::VRM_CLIMB:
		{
			const FVector Adjusted = CustomVRInputVector;

			FHitResult Hit(1.f);
			SafeMoveUpdatedComponent(Adjusted, UpdatedComponent->GetComponentQuat(), true, Hit);
			break;
		}
	}
}

void USimpleVRMovementComponent::AddCustomInputVector(const FVector& InNewInputVector)
{
	CustomVRInputVector = InNewInputVector;
}

void USimpleVRMovementComponent::ClearCustomInputVector()
{
	CustomVRInputVector = FVector::ZeroVector;
}