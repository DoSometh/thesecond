// Fill out your copyright notice in the Description page of Project Settings.

#include "GunAnimInstance.h"
#include "../Weapon/Core/VRGunBase.h"

void UGunAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Gun = Cast<AVRGunBase>(GetOwningActor());
}

void UGunAnimInstance::NativeUpdateAnimation(float Deltaseconds)
{
	Super::NativeUpdateAnimation(Deltaseconds);

	if (Gun.IsValid())
	{
		SliderIncrementPosition = Gun->GetIncrementPosition();
		bUpperSpringClip = Gun->IsUpperSpringClip();
	}
}
