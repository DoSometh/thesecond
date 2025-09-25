//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "VRInsertExtractInterface.generated.h"

class ASimpleInsertExtractActor;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UVRInsertExtractInterface : public UInterface
{
	GENERATED_BODY()
};

class SIMPLEVRFEATUREKIT_API IVRInsertExtractInterface
{
	GENERATED_BODY()

public:
	virtual ASimpleInsertExtractActor* GetInsertExtractActor() const { return NULL; }
	virtual bool IsInsertExtractActorValid() const { return GetInsertExtractActor() != NULL; }

	virtual void InsertExtractStart() {}
	virtual void InsertExtractEnd(UMotionControllerComponent* InMotionControllerComponent, USceneComponent* InHandComponent) {}
};