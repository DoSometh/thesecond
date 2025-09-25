//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "../Core/AttributeDataTableBase.h"
#include "CharacterAttributeTable.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FCharacterAttributeTable :public FAttributeDataTableBase
{
	GENERATED_USTRUCT_BODY()

	FCharacterAttributeTable();

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category = "Character Attribute")
	float Health;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Character Attribute")
	float Mana;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Character Attribute")
	float PhysicsDefense;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Character Attribute")
	float MagicDefense;
};