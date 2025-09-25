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

//������ײ����
UENUM(BlueprintType)
enum class EVRHitType :uint8
{
	VOICE_BULLET_STRIKE_HUMAN_BODY	 = 0 UMETA(DisplayName = "Bullet strike human body"),//�ӵ��������������������
	VOICE_BULLET_STRIKE_STEEL_PLATE		 UMETA(DisplayName = "Bullet strike steel plate"),//�ӵ��򵽸ְ������
	VOICE_BULLET_STRIKE_GRASSLAND		 UMETA(DisplayName = "Bullet strike grassland"),//�ӵ��򵽲ݵص�����
};