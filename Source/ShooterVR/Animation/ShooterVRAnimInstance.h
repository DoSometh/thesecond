// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ShooterVRAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERVR_API UShooterVRAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float Deltaseconds);
};
