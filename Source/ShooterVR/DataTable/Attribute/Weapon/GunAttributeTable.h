//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "../../Core/AttributeDataTableBase.h"
#include "GunAttributeTable.generated.h"

class AVRClipBase;

USTRUCT(BlueprintType, Blueprintable)
struct FGunAttributeTable :public FAttributeDataTableBase
{
	GENERATED_USTRUCT_BODY()

	FGunAttributeTable();

	//µØº–¿‡–Õ µ¿˝
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Base")
	TSubclassOf<AVRClipBase> CartridgeClipClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Gun Attribute")
	int32 BulletsNumber;
};