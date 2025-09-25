// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GunAnimInstance.generated.h"

class AVRGunBase;
/**
 * 
 */
UCLASS()
class SHOOTERVR_API UGunAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float Deltaseconds);

public:
	//捕获Slider移动意图
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GunAnim")
	FVector SliderIncrementPosition;

	//回弹堂
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GunAnim")
	bool bUpperSpringClip;
protected:
	UPROPERTY()
	TWeakObjectPtr<AVRGunBase> Gun;
};
