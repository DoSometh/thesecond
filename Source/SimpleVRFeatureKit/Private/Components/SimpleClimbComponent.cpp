// Copyright (C) RenZhai.2025.All Rights Reserved.

#include "Components/SimpleClimbComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SimpleVRMovementComponent.h"
#include "MotionControllerComponent.h"

USimpleClimbComponent::USimpleClimbComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

bool USimpleClimbComponent::TryGetVRMovement()
{
	if (ACharacter* InCharacter = Cast<ACharacter>(GetOwner()))
	{
		VRMovementComponent = Cast<USimpleVRMovementComponent>(InCharacter->GetCharacterMovement());
		if (VRMovementComponent.IsValid())
		{
			return true;
		}
	}

	return false;
}

int32 USimpleClimbComponent::StartClimb(
	AActor* InHand, 
	UMotionControllerComponent* InMotionController, 
	UPrimitiveComponent* InClimbObject)
{
	FVRClimbInfo& InInfo = ClimbInfo.AddDefaulted_GetRef();

	InInfo.HandleID = SpawnNonrepeatableHandle();
	InInfo.MotionController = InMotionController;
	InInfo.Hand = InHand;
	InInfo.ClimbObject = InClimbObject;

	InInfo.RelativeToHandTransform = InHand->GetTransform().GetRelativeTransform(
		InClimbObject->GetComponentTransform());

	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::KeepWorld, true);
	InHand->AttachToComponent(InClimbObject, AttachmentTransformRules);

	VRMovementComponent->SetMovementMode(EMovementMode::MOVE_Custom);
	VRMovementComponent->CustomMovementMode = (uint8)EVRMovementMode::VRM_CLIMB;

	return InInfo.HandleID;
}

void USimpleClimbComponent::EndClimb(int32 InHandle)
{
	FVRClimbInfo Info;
	for (auto& Tmp : ClimbInfo)
	{
		if (Tmp.HandleID == InHandle)
		{
			Info = Tmp;

			FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
			Tmp.Hand->AttachToComponent(Tmp.MotionController.Get(), AttachmentTransformRules);

			break;
		}
	}

	ClimbInfo.Remove(Info);
}

void USimpleClimbComponent::UpdateClimb(float DeltaTime)
{
	if (VRMovementComponent->MovementMode == EMovementMode::MOVE_Custom)
	{
		if (VRMovementComponent->CustomMovementMode == (uint8)EVRMovementMode::VRM_CLIMB)
		{
			for (auto& Tmp : ClimbInfo)
			{
				FVector ClimbPointWorldLocation = Tmp.ClimbObject->GetComponentTransform().TransformPosition(
					Tmp.RelativeToHandTransform.GetLocation());

				FVector NewInputVector = (Tmp.MotionController->GetComponentLocation() - ClimbPointWorldLocation) * -1.f;

				VRMovementComponent->AddCustomInputVector(NewInputVector);
			}

			if (ClimbInfo.IsEmpty())
			{
				VRMovementComponent->SetMovementMode(EMovementMode::MOVE_Walking);//更改
			}
		}
	}
}

int32 USimpleClimbComponent::SpawnNonrepeatableHandle() const
{
	int32 NewHandle = FMath::RandRange(-99999, 99999);

	if (!Contains(NewHandle) && NewHandle != INDEX_NONE)
	{
		return NewHandle;
	}

	return INDEX_NONE;
}

bool USimpleClimbComponent::Contains(int32 InHandle) const
{
	for (auto& Tmp : ClimbInfo)
	{
		if (Tmp.HandleID == InHandle)
		{
			return true;
		}
	}

	return false;
}

void USimpleClimbComponent::BeginPlay()
{
	Super::BeginPlay();

	check(TryGetVRMovement());
}

void USimpleClimbComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateClimb(DeltaTime);
}

