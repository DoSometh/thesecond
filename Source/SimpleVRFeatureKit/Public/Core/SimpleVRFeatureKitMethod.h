// Copyright (C) RenZhai.2025.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class USceneComponent;

namespace SimpleVRFeatureKitMethod
{
	FVector SIMPLEVRFEATUREKIT_API Clamp(const FVector& InValue, const FVector& InMin, const FVector& InMax);
	FRotator SIMPLEVRFEATUREKIT_API Clamp(const FRotator& InValue, const FRotator& InMin, const FRotator& InMax);
	
	bool SIMPLEVRFEATUREKIT_API IsNearlyEqual(const FVector& InA, const FVector& InB, float InAttachTolerance);
	bool SIMPLEVRFEATUREKIT_API IsNearlyEqual(const FRotator& InA, const FRotator& InB, float InAttachTolerance);

	bool SIMPLEVRFEATUREKIT_API Lerp(USceneComponent* InARootComponent, USceneComponent* InBRootComponent, float InDeltaTime, float InSpeed, float InAttachTolerance = 2.f);
	bool SIMPLEVRFEATUREKIT_API RelativeLerp(USceneComponent* InARootComponent, USceneComponent* InBRootComponent, float InDeltaTime, float InSpeed, float InAttachTolerance = 2.f);
	
	bool SIMPLEVRFEATUREKIT_API RelativeLerp(
		const FVector& ARelativeLocation, const FRotator& ARelativeRotation,
		const FVector& BRelativeLocation, const FRotator& BRelativeRotation,
		USceneComponent* InBRootComponent,
		float InDeltaTime,
		float InSpeed,
		float InAttachTolerance = 2.f);

	void SIMPLEVRFEATUREKIT_API GrabLock(const FVector& InActorStart, const FVector& InActorTaget, const FRotator& InRotatorOffset, USceneComponent* InRootComponent);
}