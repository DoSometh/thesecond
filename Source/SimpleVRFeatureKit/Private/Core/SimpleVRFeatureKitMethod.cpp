
// Copyright (C) RenZhai.2025.All Rights Reserved.
#include "Core/SimpleVRFeatureKitMethod.h"

namespace SimpleVRFeatureKitMethod
{
	FVector Clamp(const FVector& InValue, const FVector& InMin, const FVector& InMax)
	{
		return FVector(
			FMath::Clamp(InValue.X, InMin.X, InMax.X),
			FMath::Clamp(InValue.Y, InMin.Y, InMax.Y),
			FMath::Clamp(InValue.Z, InMin.Z, InMax.Z));
	}

	FRotator Clamp(const FRotator& InValue, const FRotator& InMin, const FRotator& InMax)
	{
		return FRotator(
			FMath::Clamp(InValue.Pitch, InMin.Pitch, InMax.Pitch),
			FMath::Clamp(InValue.Yaw, InMin.Yaw, InMax.Yaw),
			FMath::Clamp(InValue.Roll, InMin.Roll, InMax.Roll));
	}

	bool IsNearlyEqual(const FVector& InA, const FVector& InB, float InAttachTolerance)
	{
		return	FMath::IsNearlyEqual(InA.X, InB.X, InAttachTolerance) &&
				FMath::IsNearlyEqual(InA.Y, InB.Y, InAttachTolerance) &&
				FMath::IsNearlyEqual(InA.Z, InB.Z, InAttachTolerance);
	}

	bool IsNearlyEqual(const FRotator& InA, const FRotator& InB, float InAttachTolerance)
	{
		return 	FMath::IsNearlyEqual(InA.Yaw, InB.Yaw, InAttachTolerance) &&
				FMath::IsNearlyEqual(InA.Roll, InB.Roll, InAttachTolerance) &&
				FMath::IsNearlyEqual(InA.Pitch, InB.Pitch, InAttachTolerance);
	}

	bool Lerp(USceneComponent* InARootComponent, USceneComponent* InBRootComponent, float InDeltaTime, float InSpeed, float InAttachTolerance)
	{
		FVector AComponentLocation = InARootComponent->GetComponentLocation();
		FRotator AComponentRotation = InARootComponent->GetComponentRotation();

		FVector BComponentLocation = InBRootComponent->GetComponentLocation();
		FRotator BComponentRotation = InBRootComponent->GetComponentRotation();

		if (!IsNearlyEqual(AComponentLocation, BComponentLocation, InAttachTolerance)&&
			!IsNearlyEqual(AComponentRotation, BComponentRotation, InAttachTolerance))
		{
			BComponentLocation = FMath::Lerp(BComponentLocation, AComponentLocation, InDeltaTime * InSpeed);
			BComponentRotation = FMath::Lerp(BComponentRotation, AComponentRotation, InDeltaTime * InSpeed);

			InBRootComponent->SetWorldLocationAndRotation(BComponentLocation, BComponentRotation);
		}
		else
		{
			return true;
		}

		return false;
	}

	bool RelativeLerp(
		USceneComponent* InARootComponent, 
		USceneComponent* InBRootComponent,
		float InDeltaTime,
		float InSpeed,
		float InAttachTolerance)
	{
		FVector ARelativeLocation = InARootComponent->GetRelativeLocation();
		FRotator ARelativeRotation = InARootComponent->GetRelativeRotation();

		FVector BRelativeLocation = InBRootComponent->GetRelativeLocation();
		FRotator BRelativeRotation = InBRootComponent->GetRelativeRotation();

		if (!IsNearlyEqual(ARelativeLocation, BRelativeLocation, InAttachTolerance) &&
			!IsNearlyEqual(ARelativeRotation, BRelativeRotation, InAttachTolerance))
		{
			BRelativeLocation = FMath::Lerp(BRelativeLocation, ARelativeLocation, InDeltaTime * InSpeed);
			BRelativeRotation = FMath::Lerp(BRelativeRotation, ARelativeRotation, InDeltaTime * InSpeed);

			InBRootComponent->SetRelativeLocationAndRotation(BRelativeLocation, BRelativeRotation);
		}
		else
		{
			return true;
		}

		return false;
	}

	bool RelativeLerp(
		const FVector& ARelativeLocation, const FRotator& ARelativeRotation,
		const FVector& BRelativeLocation, const FRotator& BRelativeRotation,
		USceneComponent* InBRootComponent,
		float InDeltaTime, 
		float InSpeed,
		float InAttachTolerance)
	{
		if (InBRootComponent)
		{
			FVector CRelativeLocation = InBRootComponent->GetRelativeLocation();
			FRotator CRelativeRotation = InBRootComponent->GetRelativeRotation();

			if (!IsNearlyEqual(CRelativeLocation, BRelativeLocation, InAttachTolerance) ||
				!IsNearlyEqual(CRelativeRotation, BRelativeRotation, InAttachTolerance))
			{
				CRelativeLocation = FMath::Lerp(CRelativeLocation, BRelativeLocation, InDeltaTime * InSpeed);
				CRelativeRotation = FMath::Lerp(CRelativeRotation, BRelativeRotation, InDeltaTime * InSpeed);

				InBRootComponent->SetRelativeLocationAndRotation(CRelativeLocation, CRelativeRotation);
			}
			else
			{
				return true;
			}
		}

		return false;
	}

	void GrabLock(
		const FVector& InActorStart,
		const FVector& InActorTaget,
		const FRotator& InRotatorOffset, 
		USceneComponent* InRootComponent)
	{
		FRotator ActorRotator = FRotationMatrix::MakeFromX(InActorTaget - InActorStart).Rotator();
		InRootComponent->SetWorldRotation(ActorRotator + InRotatorOffset);
	}
}

