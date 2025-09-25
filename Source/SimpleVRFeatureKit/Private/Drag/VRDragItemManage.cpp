// Copyright (C) RenZhai.2025.All Rights Reserved.

#include "Drag/VRDragItemManage.h"

void FVRDragItemManage::Tick(float DeltaTime)
{
	for (auto &Tmp : DragSplines)
	{
		Tmp.Tick(DeltaTime);
	}
}

void FVRDragItemManage::SubmitCommand(
	AActor* InStart, 
	USceneComponent* InEnd, 
	const FVector& InTangentsValue, bool* bTrace,
	FSimpleDelegate InDragItemCompleteDelegate)
{
	for (auto& Tmp : DragSplines)
	{
		if (Tmp.IsFree())
		{
			Tmp.Init(InStart, InEnd, InTangentsValue, bTrace, InDragItemCompleteDelegate);

			return;
		}
	}

	DragSplines.AddDefaulted_GetRef().Init(InStart, InEnd, InTangentsValue, bTrace, InDragItemCompleteDelegate);
}
