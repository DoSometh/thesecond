// Copyright (C) RenZhai.2025.All Rights Reserved.

#include "Components/SimpleGrabComponent.h"
#include "MotionControllerComponent.h"
#include "SimpleVRFeatureKitLibrary.h"

// Sets default values for this component's properties
USimpleGrabComponent::USimpleGrabComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	bSimulateOnDrop = false;

	RefMotionController = nullptr;
}


bool USimpleGrabComponent::TryGrab(UMotionControllerComponent* InMotionController, AActor* InAttachActor)
{
	AttachActor = InAttachActor;
	RefMotionController = InMotionController;

	//拾取到物体产生的震动
	PlayHapticEffect(PickupFeedbackEffect);

	switch (GrabType)
	{
		case EGrabType::GRAB_FREE:
		{
			Held(InMotionController);

			GrabDelegate.Broadcast();

			return true;
		}
		case EGrabType::GRAB_SNAP:
		case EGrabType::GRAB_RELEASE:
		{
			Held(InMotionController);

			GetAttachParent()->SetRelativeRotation(GetGrabPointRelativeRotation());

			GetAttachParent()->SetWorldLocation(
				InMotionController->GetComponentLocation() + GetGrabPointRelativeLocation(),
				false, nullptr, TeleportFlagToEnum(true));

			GrabDelegate.Broadcast();

			return true;
		}
	}

	return false;
}

bool USimpleGrabComponent::TryRelease()
{
	switch (GrabType)
	{
		case EGrabType::GRAB_FREE:
		case EGrabType::GRAB_SNAP:
		case EGrabType::GRAB_RELEASE:
		{
			if (bSimulateOnDrop)
			{
				SetPrimitiveCompPhysics(true);
			}

			FDetachmentTransformRules TransformRules(EDetachmentRule::KeepWorld, true);
			GetOwner()->DetachFromActor(TransformRules);

			bHeld = false;

			//释放物体产生的震动
			PlayHapticEffect(ReleaseFeedbackEffect);

			ReleaseDelegate.Broadcast();

			RefMotionController = NULL;
			AttachActor = NULL;

			break;
		}
	}

	if (bHeld)
	{
		return false;
	}

	return true;
}

void USimpleGrabComponent::SetPrimitiveCompPhysics(bool bSimulate)
{
	if (UPrimitiveComponent* InPrimitiveComponent = Cast<UPrimitiveComponent>(GetAttachParent()))
	{
		InPrimitiveComponent->SetSimulatePhysics(bSimulate);
	}
}

bool USimpleGrabComponent::AttachParentToMotionController(UMotionControllerComponent* InMotionController)
{
	if (GetAttachParent())
	{
		FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::KeepWorld, true);
		return GetAttachParent()->AttachToComponent(InMotionController, AttachmentTransformRules);
	}

	return false;
}

bool USimpleGrabComponent::PlayHapticEffect(UHapticFeedbackEffect_Base* InEffect,float InScale,bool bLoop)
{
	return USimpleVRFeatureKitLibrary::PlayHapticEffect(InEffect, RefMotionController,InScale, bLoop);
}

void USimpleGrabComponent::SetGrabType(EGrabType InGrabType)
{
	GrabType = InGrabType;
}

FRotator USimpleGrabComponent::GetGrabPointRelativeRotation() const
{
	return GetRelativeRotation().GetInverse();
}

FVector USimpleGrabComponent::GetGrabPointRelativeLocation() const
{
	return (GetComponentLocation() - GetAttachParent()->GetComponentLocation()) * (-1.f);
}

EGrabTrackingType USimpleGrabComponent::GetGrabTrackingType()
{
	if (bHeld)
	{
		if (RefMotionController)
		{
			EControllerHand ControllerHand = USimpleVRFeatureKitLibrary::GetControllerHand(RefMotionController->MotionSource.ToString());
		
			switch (ControllerHand)
			{
			case EControllerHand::Left:
				return EGrabTrackingType::GRAB_LEFT;
			case EControllerHand::Right:
				return EGrabTrackingType::GRAB_RIGHT;
			case EControllerHand::AnyHand:
				return EGrabTrackingType::GRAB_ANYTRACKING;
			case EControllerHand::Pad:
				return EGrabTrackingType::GRAB_PAD;
			case EControllerHand::ExternalCamera:
				return EGrabTrackingType::GRAB_EXTERNALCAMERA;
			case EControllerHand::Gun:
				return EGrabTrackingType::GRAB_GUN;
			case EControllerHand::HMD:
				return EGrabTrackingType::GRAB_HMD;
			case EControllerHand::ControllerHand_Count:
				return EGrabTrackingType::GRAB_HAND_COUNT;
			}
		}
	}

	return EGrabTrackingType::GRAB_NONE;
}

void USimpleGrabComponent::InitGrabComponent()
{
	if (UPrimitiveComponent* InPrimitiveComponent = Cast<UPrimitiveComponent>(GetAttachParent()))
	{
		bSimulateOnDrop = InPrimitiveComponent->IsAnySimulatingPhysics();
	}
}

// Called when the game starts
void USimpleGrabComponent::BeginPlay()
{
	Super::BeginPlay();

}

void USimpleGrabComponent::Held(UMotionControllerComponent* InMotionController)
{
	SetPrimitiveCompPhysics(false);

	AttachParentToMotionController(InMotionController);

	bHeld = true;
}

// Called every frame
void USimpleGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

