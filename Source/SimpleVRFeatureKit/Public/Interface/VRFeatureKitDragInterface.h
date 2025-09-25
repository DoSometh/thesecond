//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "VRFeatureKitDragInterface.generated.h"

class UMotionControllerComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UVRFeatureKitDragInterface : public UInterface
{
	GENERATED_BODY()
};

class SIMPLEVRFEATUREKIT_API IVRFeatureKitDragInterface
{
	GENERATED_BODY()

public:

	virtual void OnStartDraged() {}
	virtual void OnEndDraged() {}
};