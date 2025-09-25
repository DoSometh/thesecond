//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "VRFeatureKitInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UVRFeatureKitInterface : public UInterface
{
	GENERATED_BODY()
};

class SIMPLEVRFEATUREKIT_API IVRFeatureKitInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetVRFeatureKitID()const { return INDEX_NONE; }
	virtual bool TryRelease() { return false; }

	virtual void OnAttached() {}
	virtual void OnEndAttached() {}
public:
	virtual bool IsValidAttachID() const { return GetVRFeatureKitID() != INDEX_NONE; }
};