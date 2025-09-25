// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShooterVRGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERVR_API UShooterVRGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init();

	virtual void Shutdown();
};
