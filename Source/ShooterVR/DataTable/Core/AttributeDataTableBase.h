//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AttributeDataTableBase.generated.h"

USTRUCT(BlueprintType)
struct FAttributeDataTableBase :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FAttributeDataTableBase();

	//指向自己的ID
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Base")
	int32 ID;

	//名字
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Base")
	FText Name;

	//图标
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Base")
	UTexture2D* Icon;

	//实例
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Base")
	TSubclassOf<AActor> ActorObjectClass;

	//属性
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Attribute Base")
	float PhysicsAttack;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Attribute Base")
	float MagicAttack;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Attribute Base")
	float EmpiricalValue;
};