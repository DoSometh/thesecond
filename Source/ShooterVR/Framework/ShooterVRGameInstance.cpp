// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterVRGameInstance.h"
#include "ShooterVR/Common/Tickable/GlobalTickable.h"

void UShooterVRGameInstance::Init()
{
	Super::Init();

	//×¢²áÈ«¾Ötick
	FGlobalTickable::Get();
}

void UShooterVRGameInstance::Shutdown()
{
	Super::Shutdown();
}