// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShooterVRType.generated.h"

UENUM(BlueprintType)
enum class EVRHandType :uint8
{
	VR_RIGHT UMETA(DisplayName = "Right"),
	VR_LEFT  UMETA(DisplayName = "Left"),
	VR_MAX   UMETA(DisplayName = "Max"),
};

//关于碰撞声音
UENUM(BlueprintType)
enum class EVRHitType :uint8
{
	VOICE_BULLET_STRIKE_HUMAN_BODY	 = 0 UMETA(DisplayName = "Bullet strike human body"),//子弹打到类人生物的肉体声音
	VOICE_BULLET_STRIKE_STEEL_PLATE		 UMETA(DisplayName = "Bullet strike steel plate"),//子弹打到钢板的声音
	VOICE_BULLET_STRIKE_GRASSLAND		 UMETA(DisplayName = "Bullet strike grassland"),//子弹打到草地的声音
};