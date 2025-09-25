// Copyright (C) RenZhai.2025.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Drag/VRDragItemObject.h"
#include "VRDragItemManage.generated.h"

USTRUCT(BlueprintType)
struct SIMPLEVRFEATUREKIT_API FVRDragItemManage
{
	GENERATED_USTRUCT_BODY()

	void Tick(float DeltaTime);

	void SubmitCommand(AActor* InStart, USceneComponent* InEnd, const FVector& InTangentsValue, bool* bTrace = NULL,FSimpleDelegate InDragItemCompleteDelegate = FSimpleDelegate());

private:
	UPROPERTY()
	TArray<FVRDragItemObject> DragSplines;
};