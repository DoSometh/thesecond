// Copyright (C) RenZhai.2020.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ShooterVR/DataRegistry/VRDataRegistryManage.h"
#include "ShooterVRFunctionLibrary.generated.h"

UCLASS()
class UShooterVRFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "ShooterVRFunctionLibrary|Voice")
	static bool FindVoiceCached(EVRHitType InHitType, FVoiceTable& OutItem);

	UFUNCTION(BlueprintCallable, Category = "ShooterVRFunctionLibrary|Effect")
	static bool FindEffectCached(EVRHitType InHitType, FEffectTable& OutItem);
};