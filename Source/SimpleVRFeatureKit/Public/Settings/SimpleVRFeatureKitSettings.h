// Copyright (C) RenZhai.2020.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SimpleVRFeatureKitSettings.generated.h"

UCLASS(config = SimpleVRFeatureKitSettings)
class SIMPLEVRFEATUREKIT_API USimpleVRFeatureKitSettings : public UObject
{
	GENERATED_BODY()

public:
	USimpleVRFeatureKitSettings();

	UPROPERTY(config, EditAnywhere, Category = DragDebugSettings, meta = (ToolTip = "YX"))
	bool bDrawDrag;

	UPROPERTY(config, EditAnywhere, Category = DragDebugSettings, meta = (EditCondition = "bDrawDrag",ToolTip = "YX"))
	int32 DragSubsection;

	UPROPERTY(config, EditAnywhere, Category = DragDebugSettings, meta = (EditCondition = "bDrawDrag",ToolTip = "YX"))
	float SphereRadius;

	UPROPERTY(config, EditAnywhere,  Category = DragDebugSettings, meta = (EditCondition = "bDrawDrag", ToolTip = "YX"))
	FColor SphereColor;

	UPROPERTY(config, EditAnywhere,  Category = DragDebugSettings, meta = (EditCondition = "bDrawDrag", ToolTip = "YX"))
	int32 SphereSegments;

	UPROPERTY(config, EditAnywhere, Category = Drag, meta = (ToolTip = "YX"))
	float DragVelocity;
};