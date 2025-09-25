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

	//ָ���Լ���ID
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Base")
	int32 ID;

	//����
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Base")
	FText Name;

	//ͼ��
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Base")
	UTexture2D* Icon;

	//ʵ��
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Base")
	TSubclassOf<AActor> ActorObjectClass;

	//����
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Attribute Base")
	float PhysicsAttack;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Attribute Base")
	float MagicAttack;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Attribute Base")
	float EmpiricalValue;
};