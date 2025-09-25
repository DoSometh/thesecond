// Copyright (C) RenZhai.2025.All Rights Reserved.

#include "Components/SimpleClipComponent.h"

USimpleClipComponent::USimpleClipComponent()
{
	ShapeColor = FColor(0, 255, 0, 255);
}

void USimpleClipComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USimpleClipComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

