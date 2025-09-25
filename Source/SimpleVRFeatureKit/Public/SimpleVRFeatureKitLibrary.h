// Copyright (C) RenZhai.2020.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SimpleVRFeatureKitLibrary.generated.h"

class USimpleGrabComponent;
class UMotionControllerComponent;
class UHapticFeedbackEffect_Base;
class ASimpleInsertExtractActor;

enum class EControllerHand : uint8;

UCLASS()
class SIMPLEVRFEATUREKIT_API USimpleVRFeatureKitLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "VRFeatureKit|GrabComponent")
	static bool GetSimpleGrabComponentsByActor(AActor* InActor, TArray<USimpleGrabComponent*>& OutGrabComponents);

	UFUNCTION(BlueprintCallable, Category = "VRFeatureKit|GrabComponent")
	static USimpleGrabComponent* GetSimpleGrabComponentByActor(AActor* InActor, int32 Index = 0);

	UFUNCTION(BlueprintCallable, Category = "HapticEffect|GrabComponent")
	static EControllerHand GetControllerHand(const FString& InControllerTypeString);

	//可以由上层调用
	UFUNCTION(BlueprintCallable, Category = "HapticEffect|GrabComponent")
	static bool PlayHapticEffect(UHapticFeedbackEffect_Base* InEffect, UMotionControllerComponent* InMotionController,float InScale = 1.f, bool bLoop = false);

	UFUNCTION(BlueprintCallable, meta = (Category = "InsertExtract", WorldContext = WorldContextObject))
	static ASimpleInsertExtractActor* SpawnInsertExtractActorAndPlay(
			UObject* WorldContextObject,
			USceneComponent* InAttachParent,
			const FInsertExtractInfo& InInsertExtractInfo,
			const FVector& InLocation,
			const FVector& InImpactNormal);

	UFUNCTION(BlueprintPure, Category = "Animinstance")
	static FVector ToControlRigType1(const FVector& InOwnerLocation);

	UFUNCTION(BlueprintPure, Category = "Animinstance")
	static FVector ToControlRigType2(const FVector& InOwnerLocation);

	UFUNCTION(BlueprintPure, Category = "Animinstance")
	static FVector ToControlRigType3(const FVector& InOwnerLocation);

	UFUNCTION(BlueprintPure, Category = "Animinstance")
	static FVector ToControlRigType4(const FVector& InOwnerLocation);

	UFUNCTION(BlueprintPure, Category = "Animinstance")
	static FVector ToControlRigType5(const FVector& InOwnerLocation);

	UFUNCTION(BlueprintPure, Category = "Animinstance")
	static FVector ToControlRigType6(const FVector& InOwnerLocation);
};