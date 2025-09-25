//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "VRGrabInterface.generated.h"

class UMotionControllerComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UVRGrabInterface : public UInterface
{
	GENERATED_BODY()
};

class SIMPLEVRFEATUREKIT_API IVRGrabInterface
{
	GENERATED_BODY()

public:
	virtual bool IsGrab() const { return false; }

	virtual void StartLockGrab() {}
	virtual void LockGrab(USceneComponent *InBoxComponent) {}
	virtual void EndLockGrab() {}

	virtual UMotionControllerComponent* GetMotionController() const { return NULL; }
};