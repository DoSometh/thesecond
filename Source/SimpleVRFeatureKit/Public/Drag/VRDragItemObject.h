// Copyright (C) RenZhai.2025.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VRDragItemObject.generated.h"

enum class EVRItemObjectState : uint8;
class USplineComponent;

USTRUCT(BlueprintType)
struct SIMPLEVRFEATUREKIT_API FVRDragItemObject
{
	GENERATED_USTRUCT_BODY()

	FVRDragItemObject();

	FSimpleDelegate OnDragItemCompleteDelegate;

	//队列状态
	UPROPERTY()
	EVRItemObjectState DragState;

	UPROPERTY()
	FVector EndPoint;

	UPROPERTY()
	USceneComponent* EndObject;

	UPROPERTY()
	AActor* StartObject;

	UPROPERTY()
	float Time;

	//轨迹
	UPROPERTY()
	TObjectPtr<USplineComponent> Spline;

private:
	bool* bTraceObject;

public:
	bool IsFree() const;

	void Tick(float DeltaTime);

	void Init(AActor* InStart, USceneComponent* InEnd, const FVector& InTangentsValue, bool* bTrace, FSimpleDelegate InDragItemCompleteDelegate);
};