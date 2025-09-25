// Copyright (C) RenZhai.2025.All Rights Reserved.

#include "Components/SimpleInsertExtractComponent.h"
#include "Interface/VRInsertExtractInterface.h"
#include "MotionControllerComponent.h"

USimpleInsertExtractComponent::USimpleInsertExtractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	InitializeRelativePosition = FVector::ZeroVector;
}

void USimpleInsertExtractComponent::Start(
	const FInsertExtractInfo& InInsertExtractInfo, 
	const FVector& InImpactNormal)
{
	if (InInsertExtractInfo.MotionControllerComponent.IsValid())
	{
		InsertExtractInfo = InInsertExtractInfo;

		SetRelativeLocation(FVector::ZeroVector);
		SetRelativeRotation(FRotator::ZeroRotator);

		FRotator InsertExtractRotation = (InImpactNormal * -1.f).ToOrientationRotator();
		SetWorldRotation(InsertExtractRotation);

		FAttachmentTransformRules AttachmentTransformRules(
			EAttachmentRule::KeepWorld, true);

		check(InInsertExtractInfo.AttachedComponent->AttachToComponent(this, AttachmentTransformRules));
		check(InInsertExtractInfo.Hand->AttachToComponent(this, AttachmentTransformRules));

		InitializeRelativePosition = GetInsertExtractRelativePosition();

		if (IVRInsertExtractInterface *InExtractInterface = Cast<IVRInsertExtractInterface>(InInsertExtractInfo.AttachedComponent->GetOwner()))
		{
			InExtractInterface->InsertExtractStart();
		}
	}
}

void USimpleInsertExtractComponent::End()
{
	if (InsertExtractInfo.MotionControllerComponent.IsValid() && 
		InsertExtractInfo.Hand.IsValid())
	{
		FAttachmentTransformRules AttachmentTransformRules(
			EAttachmentRule::SnapToTarget, true);

		InsertExtractInfo.Hand->AttachToComponent(InsertExtractInfo.MotionControllerComponent.Get(), AttachmentTransformRules);
	
		if (IVRInsertExtractInterface* InInsertExtractInterface = Cast<IVRInsertExtractInterface>(InsertExtractInfo.AttachedComponent->GetOwner()))
		{
			InInsertExtractInterface->InsertExtractEnd(
				InsertExtractInfo.MotionControllerComponent.Get(),
				InsertExtractInfo.Hand.Get());
		}

		InsertExtractInfo.MotionControllerComponent = NULL;
	}
}

FVector USimpleInsertExtractComponent::GetInsertExtractRelativePosition() const
{
	if (InsertExtractInfo.MotionControllerComponent.IsValid())
	{
		FVector OutClosestPoint;

		FMath::PointDistToLine(
			InsertExtractInfo.MotionControllerComponent->GetComponentLocation(),
			InsertExtractInfo.InsertDirection,
			GetComponentLocation(), OutClosestPoint);

		if (USceneComponent* InMyParentComponent = GetAttachParent())
		{
			return InMyParentComponent->GetComponentTransform().InverseTransformPosition(OutClosestPoint);
		}
	}

	return FVector::ZeroVector;
}

void USimpleInsertExtractComponent::Registration(UMotionControllerComponent* InMotionControllerComponent, USceneComponent* InHand)
{
	InsertExtractInfo.MotionControllerComponent = InMotionControllerComponent;
	InsertExtractInfo.Hand = InHand;

	FAttachmentTransformRules AttachmentTransformRules(
		EAttachmentRule::KeepWorld, true);

	//吸附到对应点
	check(InHand->AttachToComponent(this, AttachmentTransformRules));
}

void USimpleInsertExtractComponent::Deregistration()
{
	if (InsertExtractInfo.MotionControllerComponent.IsValid())
	{
		FAttachmentTransformRules AttachmentTransformRules(
			EAttachmentRule::SnapToTarget, true);

		check(InsertExtractInfo.Hand->AttachToComponent(
			InsertExtractInfo.MotionControllerComponent.Get(),
			AttachmentTransformRules));

		InsertExtractInfo.MotionControllerComponent = NULL;
		InsertExtractInfo.Hand = NULL;
	}
}

void USimpleInsertExtractComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USimpleInsertExtractComponent::CheckAttachedComponentParent(USceneComponent* InNewSceneComponent)
{
	if (InNewSceneComponent)
	{
		if (!InNewSceneComponent->IsAttachedTo(this))
		{
			FAttachmentTransformRules AttachmentTransformRules(
				EAttachmentRule::KeepWorld, true);

			check(InNewSceneComponent->AttachToComponent(this, AttachmentTransformRules));
		}
	}
}

void USimpleInsertExtractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType,ThisTickFunction);

	if (InsertExtractInfo.MotionControllerComponent.IsValid())
	{
		CheckAttachedComponentParent(InsertExtractInfo.Hand.Get());
		CheckAttachedComponentParent(InsertExtractInfo.AttachedComponent.Get());

		float Length = FMath::Max3(InsertExtractInfo.Extend.X, InsertExtractInfo.Extend.Y, InsertExtractInfo.Extend.Z);
	
		if (USceneComponent* InComponent = GetAttachParent())
		{
			FVector InsertNormalDirection = InsertExtractInfo.InsertDirection.GetSafeNormal();
			FVector OriginPoint = InComponent->GetComponentLocation() + InsertNormalDirection * Length;
		
			float InDistance = FVector::Distance(GetComponentLocation(), OriginPoint);
			if (InDistance < (Length + InsertExtractInfo.LengthOffset))
			{
				FVector MyRelativeLocation = GetInsertExtractRelativePosition();
				FVector CurrentRelativeInitializeLocation = MyRelativeLocation - InitializeRelativePosition;

				SetRelativeLocation(CurrentRelativeInitializeLocation);
			}
			else
			{
				End();

				InComponent->GetOwner()->Destroy();
			}
		}
	}
}
