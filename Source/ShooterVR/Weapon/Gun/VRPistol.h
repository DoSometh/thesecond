// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/VRGunBase.h"
#include "VRPistol.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERVR_API AVRPistol : public AVRGunBase
{
	GENERATED_BODY()

public:
	AVRPistol();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
