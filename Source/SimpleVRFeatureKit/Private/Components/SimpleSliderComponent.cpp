// Copyright (C) RenZhai.2025.All Rights Reserved.

#include "Components/SimpleSliderComponent.h"
#include "Core/SimpleVRFeatureKitMethod.h"

USimpleSliderComponent::USimpleSliderComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SliderRelativeDistance = 5.f;
	bGrab = false;
	SpringbackSpeed = 2.f;
	bSpringback = true;

	bEnablePosition = true;
	bEnablePositionX = true;
	bEnablePositionY = true;
	bEnablePositionZ = false;
	bEnablePositionNegativeX = true;
	bEnablePositionPositiveX = true;
	bEnablePositionNegativeY = true;
	bEnablePositionPositiveY = true;
	bEnablePositionNegativeZ = true;
	bEnablePositionPositiveZ = true;

	bEnableRotator = true;
	bEnableRotatorYaw = true;
	bEnableRotatorRoll = true;
	bEnableRotatorPitch = true;

	bEnableStartSpringbackEvent = true;
	bEnableStartPullEvent = true;

	ShapeColor = FColor(0, 255, 255, 255);
}

void USimpleSliderComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeRelativePosition = GetRelativeLocation();
	InitializeRelativeRotator = GetRelativeRotation();
}

void USimpleSliderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bSpringback)
	{
		if (bGrab)
		{
			StartSlider(DeltaTime);
		}
		else
		{
			EndAutomaticSlider(DeltaTime);
		}
	}
	else
	{
		if (bGrab)
		{
			if (bEnableStartSpringbackEvent)
			{
				StartSlider(DeltaTime);
			}
			else
			{
				EndSlider(DeltaTime);
			}
		}
	}
}

FVector USimpleSliderComponent::IsAllowPosition(const FVector& InVector)
{
	return FVector(
		IsAllowInputXAxis(InVector),
		IsAllowInputYAxis(InVector),
		IsAllowInputZAxis(InVector));
}

FVector USimpleSliderComponent::IsAllowPNPosition(const FVector& InVector)
{
	return FVector(
		IsAllowInputXPNAxis(InVector),
		IsAllowInputYPNAxis(InVector),
		IsAllowInputZPNAxis(InVector));
}

FRotator USimpleSliderComponent::IsAllowRotator(const FRotator& InRotator)
{
	return FRotator(
		IsAllowInputPitchAxis(InRotator),
		IsAllowInputYawAxis(InRotator),
		IsAllowInputRollAxis(InRotator));
}

void USimpleSliderComponent::StartSlider(float DeltaTime)
{
	if (bEnablePosition)
	{
		float CurrentDistance = FVector::Distance(
			IsAllowPosition(DragPosition),
			IsAllowPosition(InitializeDragPosition));

		if (CurrentDistance < SliderRelativeDistance)
		{
			IncrementPosition = IsAllowPNPosition(DragPosition - InitializeDragPosition);

			SetRelativeLocation(IncrementPosition + InitializeRelativePosition);

			if (bEnableStartPullEvent)
			{
				bEnableStartPullEvent = false;
				StartPullupDelegate.Broadcast();
			}

			if (SlidingDelegate.IsBound())
			{
				float InRatio = CurrentDistance / SliderRelativeDistance;
				SlidingDelegate.Broadcast(InRatio, false);
			}
		}
		else
		{
			if (bEnableStartSpringbackEvent)
			{
				bEnableStartSpringbackEvent = false;

				EndPullupDelegate.Broadcast();
			}
		}
	}

	if (bEnableRotator)
	{

	}
}

void USimpleSliderComponent::EndAutomaticSlider(float DeltaTime)
{
	FVector CurrentRelativePosition = GetRelativeLocation();

	if (!SimpleVRFeatureKitMethod::IsNearlyEqual(
		InitializeRelativePosition,
		CurrentRelativePosition, 0.1f))
	{
		CurrentRelativePosition = FMath::Lerp(CurrentRelativePosition, InitializeRelativePosition, DeltaTime * SpringbackSpeed);
		SetRelativeLocation(CurrentRelativePosition);

		IncrementPosition = CurrentRelativePosition - InitializeRelativePosition;

		if (!bEnableStartPullEvent)
		{
			bEnableStartPullEvent = true;

			StartSpringbackDelegate.Broadcast();
		}

		if (SlidingDelegate.IsBound())
		{
			float CurrentDistance = IncrementPosition.Size();

			float InRatio = CurrentDistance / SliderRelativeDistance;
			SlidingDelegate.Broadcast(InRatio, true);
		}
	}
	else
	{
		if (!bEnableStartSpringbackEvent)
		{
			bEnableStartSpringbackEvent = true;

			EndSpringbackDelegate.Broadcast();
		}
	}
}

void USimpleSliderComponent::EndSlider(float DeltaTime)
{
	if (bEnablePosition)
	{
		FVector CurrentRelativePosition = GetRelativeLocation();

		float CurrentDistance = FVector::Distance(
			IsAllowPosition(DragPosition),
			IsAllowPosition(InitializeDragPosition));

		FVector IncrementPositionA = IsAllowPNPosition(DragPosition - InitializeDragPosition);

		if (!bEnableStartSpringbackEvent)
		{
			if (IncrementPositionA.Size() == 0.f)
			{
				FVector IncrementPositionB = IsAllowPNPosition(CurrentRelativePosition - InitializeRelativePosition);
				if (IncrementPositionB.Size() != 0.f)
				{
					//如果不相等 重新推测出一个新的 InitializeDragPosition
					if (!SimpleVRFeatureKitMethod::IsNearlyEqual(
						IncrementPositionA,
						IncrementPositionB, 0.1f))
					{
						InitializeDragPosition = DragPosition - IncrementPositionB;
						IncrementPositionA = IncrementPositionB;
					}
				}
			}
		}

		if (CurrentDistance < SliderRelativeDistance)
		{
			IncrementPosition = IncrementPositionA;

			SetRelativeLocation(IncrementPosition + InitializeRelativePosition);

			if (!bEnableStartPullEvent)
			{
				bEnableStartPullEvent = true;
				StartSpringbackDelegate.Broadcast();
			}

			if (SlidingDelegate.IsBound())
			{
				float InRatio = CurrentDistance / SliderRelativeDistance;
				SlidingDelegate.Broadcast(InRatio, false);
			}
		}

		if (SimpleVRFeatureKitMethod::IsNearlyEqual(
			InitializeRelativePosition,
			CurrentRelativePosition, 0.1f))
		{
			if (!bEnableStartSpringbackEvent)
			{
				bEnableStartSpringbackEvent = true;

				EndSpringbackDelegate.Broadcast();

				InitializeDragPosition = DragPosition;

				SetRelativeLocation(InitializeRelativePosition);
			}
		}
	}
}

float USimpleSliderComponent::IsAllowInputXPNAxis(const FVector& InVector)
{
	return bEnablePositionX ? IsAllowInputPNAxis(bEnablePositionNegativeX, bEnablePositionPositiveX, InVector.X) : 0.f;
}

float USimpleSliderComponent::IsAllowInputYPNAxis(const FVector& InVector)
{
	return bEnablePositionY ? IsAllowInputPNAxis(bEnablePositionNegativeY, bEnablePositionPositiveY, InVector.Y) : 0.f;
}

float USimpleSliderComponent::IsAllowInputZPNAxis(const FVector& InVector)
{
	return bEnablePositionZ ? IsAllowInputPNAxis(bEnablePositionNegativeZ, bEnablePositionPositiveZ, InVector.Z) : 0.f;
}

float USimpleSliderComponent::IsAllowInputXAxis(const FVector& InVector)
{
	return bEnablePositionX ? InVector.X : 0.f;
}

float USimpleSliderComponent::IsAllowInputYAxis(const FVector& InVector)
{
	return bEnablePositionY ? InVector.Y : 0.f;
}

float USimpleSliderComponent::IsAllowInputZAxis(const FVector& InVector)
{
	return bEnablePositionZ ? InVector.Z : 0.f;
}

float USimpleSliderComponent::IsAllowInputYawAxis(const FRotator& InRotator)
{
	return bEnableRotatorYaw ? InRotator.Yaw : 0.f;
}

float USimpleSliderComponent::IsAllowInputRollAxis(const FRotator& InRotator)
{
	return bEnableRotatorRoll ? InRotator.Roll : 0.f;
}

float USimpleSliderComponent::IsAllowInputPitchAxis(const FRotator& InRotator)
{
	return bEnableRotatorPitch ? InRotator.Pitch : 0.f;
}

float USimpleSliderComponent::IsAllowInputPNAxis(bool bNegative, bool bPositive, float InValue)
{
	if (InValue < 0.f)
	{
		if (bNegative)
		{
			return InValue;
		}
	}
	else if (InValue > 0.f)
	{
		if (bPositive)
		{
			return InValue;
		}
	}

	return 0.f;
}
