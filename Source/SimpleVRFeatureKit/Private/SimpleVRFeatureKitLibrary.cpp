// Copyright (C) RenZhai.2025.All Rights Reserved.

#include "SimpleVRFeatureKitLibrary.h"
#include "MotionControllerComponent.h"
#include "Components/SimpleGrabComponent.h"
#include "Actor/SimpleInsertExtractActor.h"
#include "Engine/World.h"

USimpleVRFeatureKitLibrary::USimpleVRFeatureKitLibrary(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

bool USimpleVRFeatureKitLibrary::GetSimpleGrabComponentsByActor(AActor* InActor, TArray<USimpleGrabComponent*>& OutGrabComponents)
{
	if (InActor)
	{
		TArray<UActorComponent*> Components;
		InActor->GetComponents(USimpleGrabComponent::StaticClass(), Components);

		for (auto& Tmp : Components)
		{
			OutGrabComponents.Add(Cast<USimpleGrabComponent>(Tmp));
		}
	}

	return OutGrabComponents.Num() > 0;
}

USimpleGrabComponent* USimpleVRFeatureKitLibrary::GetSimpleGrabComponentByActor(AActor* InActor, int32 Index)
{
	TArray<USimpleGrabComponent*> Components;
	if (GetSimpleGrabComponentsByActor(InActor, Components))
	{
		if (Components.IsValidIndex(Index))
		{
			return Components[Index];
		}
	}

	return NULL;
}

EControllerHand USimpleVRFeatureKitLibrary::GetControllerHand(const FString& InControllerTypeString)
{
	if (InControllerTypeString == TEXT("Left"))
	{
		return EControllerHand::Left;
	}
	else if (InControllerTypeString == TEXT("Right"))
	{
		return EControllerHand::Right;
	}
	else if (InControllerTypeString == TEXT("Gun"))
	{
		return EControllerHand::Gun;
	}
	else if (InControllerTypeString == TEXT("HMD"))
	{
		return EControllerHand::HMD;
	}
	else if (InControllerTypeString == TEXT("AnyHand"))
	{
		return EControllerHand::AnyHand;
	}
	else if (InControllerTypeString == TEXT("ExternalCamera"))
	{
		return EControllerHand::ExternalCamera;
	}
	else if (InControllerTypeString == TEXT("Pad"))
	{
		return EControllerHand::Pad;
	}
	else if (InControllerTypeString == TEXT("ControllerHand_Count"))
	{
		return EControllerHand::ControllerHand_Count;
	}

	return (EControllerHand)255;
}

bool USimpleVRFeatureKitLibrary::PlayHapticEffect(UHapticFeedbackEffect_Base* InEffect, UMotionControllerComponent* InMotionController, float InScale , bool bLoop )
{
	if (InMotionController)
	{
		if (APawn* InPawn = InMotionController->GetOwner<APawn>())
		{
			if (APlayerController* InPlayerController = InPawn->GetController<APlayerController>())
			{
				InPlayerController->PlayHapticEffect(
					InEffect,
					GetControllerHand(InMotionController->MotionSource.ToString()),InScale,bLoop);
			}
		}
	}

	return false;
}

ASimpleInsertExtractActor* USimpleVRFeatureKitLibrary::SpawnInsertExtractActorAndPlay(UObject* WorldContextObject, USceneComponent* InAttachParent, const FInsertExtractInfo& InInsertExtractInfo, const FVector& InLocation, const FVector& InImpactNormal)
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		FTransform Transform(InInsertExtractInfo.InsertDirection.Rotation().Quaternion(),
			InLocation);

		if (ASimpleInsertExtractActor* InsertExtractActor = World->SpawnActorDeferred<ASimpleInsertExtractActor>(
			ASimpleInsertExtractActor::StaticClass(),
			Transform,
			InAttachParent->GetOwner(),
			Cast<APawn>(InAttachParent->GetOwner()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn))
		{
			InsertExtractActor->PreInit();

			InsertExtractActor->PostInit();

			InsertExtractActor->FinishSpawning(Transform);

			if (InAttachParent)
			{
				FAttachmentTransformRules AttachmentTransformRules(
					EAttachmentRule::SnapToTarget,
					EAttachmentRule::KeepWorld,
					EAttachmentRule::KeepWorld, true);

				InsertExtractActor->AttachToComponent(InAttachParent, AttachmentTransformRules, InInsertExtractInfo.AttachName);
			}

			InsertExtractActor->Start(
				InInsertExtractInfo,
				InImpactNormal);

			return InsertExtractActor;
		}
	}

	return nullptr;
}

FVector USimpleVRFeatureKitLibrary::ToControlRigType1(const FVector& InOwnerLocation)
{
	return FVector(-InOwnerLocation.Y, InOwnerLocation.Z, -InOwnerLocation.X);
}

FVector USimpleVRFeatureKitLibrary::ToControlRigType2(const FVector& InOwnerLocation)
{
	return FVector(-InOwnerLocation.Y, -InOwnerLocation.Z, InOwnerLocation.X);
}

FVector USimpleVRFeatureKitLibrary::ToControlRigType3(const FVector& InOwnerLocation)
{
	return FVector(InOwnerLocation.Z,InOwnerLocation.X, InOwnerLocation.Y);
}

FVector USimpleVRFeatureKitLibrary::ToControlRigType4(const FVector& InOwnerLocation)
{
	return FVector(InOwnerLocation.Z, -InOwnerLocation.X, -InOwnerLocation.Y);
}

FVector USimpleVRFeatureKitLibrary::ToControlRigType5(const FVector& InOwnerLocation)
{
	return FVector(-InOwnerLocation.Y,-InOwnerLocation.X, -InOwnerLocation.Z);
}

FVector USimpleVRFeatureKitLibrary::ToControlRigType6(const FVector& InOwnerLocation)
{
	return FVector(-InOwnerLocation.Z,InOwnerLocation.X, -InOwnerLocation.Y);
}
