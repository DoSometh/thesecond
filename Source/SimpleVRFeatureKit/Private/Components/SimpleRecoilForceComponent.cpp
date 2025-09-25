// Copyright (C) RenZhai.2025.All Rights Reserved.

#include "Components/SimpleRecoilForceComponent.h"
#include "Core/SimpleVRFeatureKitMethod.h"
#include "Components/SceneComponent.h"

USimpleRecoilForceComponent::USimpleRecoilForceComponent()
	:bEnableRecoilForce(true)
	,RecoilForceOffset(30.f, 0.f, 0.f)
{
	PrimaryComponentTick.bCanEverTick = true;

	bRecoilForce = false;
}

void USimpleRecoilForceComponent::PlayRecoilForce()
{
	if (bEnableRecoilForce)
	{
		IncrementRotator = RecoilForceOffset;

		ResetAttachRootComponentRotator();

		bRecoilForce = true;
	}
}

void USimpleRecoilForceComponent::RegisterRecoilForce()
{
	if (bEnableRecoilForce)
	{
		if (AActor* InOwner = GetOwner())
		{
			if (USceneComponent* InAttachParent = InOwner->GetRootComponent()->GetAttachParent())
			{
				AttachRootComponent = InAttachParent;
			}
			else
			{
				AttachRootComponent = InOwner->GetRootComponent();
			}
		}
	}
}

void USimpleRecoilForceComponent::UnregisteredRecoilForce()
{
	IncrementRotator = FRotator::ZeroRotator;
	AttachRootComponent = NULL;
}

void USimpleRecoilForceComponent::ResetAttachRootComponentRotator()
{
	AttachRootComponent->SetRelativeRotation(AttachRootComponent->GetRelativeRotation() + IncrementRotator);
}

void USimpleRecoilForceComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USimpleRecoilForceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bEnableRecoilForce)
	{
		if (bRecoilForce)
		{
			if (AttachRootComponent.IsValid())
			{
				if (!SimpleVRFeatureKitMethod::IsNearlyEqual(IncrementRotator, FRotator::ZeroRotator, 1.f))
				{
					IncrementRotator = FMath::Lerp(IncrementRotator, FRotator::ZeroRotator, DeltaTime * 10.f);

					ResetAttachRootComponentRotator();
				}
				else
				{
					IncrementRotator = FRotator::ZeroRotator;

					bRecoilForce = false;
				}
			}
		}
	}
}
