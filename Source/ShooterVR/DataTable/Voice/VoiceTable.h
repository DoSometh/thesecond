//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "../../ShooterVRType.h"
#include "VoiceTable.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FVoiceTable :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FVoiceTable();

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category = "Voice")
	EVRHitType VoiceType;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category = "Voice")
	USoundBase* SoundCue;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category = "Voice")
	USoundAttenuation* SoundAttenuation;
};