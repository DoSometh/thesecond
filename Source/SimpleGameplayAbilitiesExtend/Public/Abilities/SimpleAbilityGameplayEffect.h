// Copyright (C) RenZhai.2025.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "SimpleAbilityGameplayEffect.generated.h"

UCLASS()
class SIMPLEGAMEPLAYABILITIESEXTEND_API USimpleAbilityGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()

	//用于UI查找数值
	UPROPERTY(EditDefaultsOnly, Category = Tip)
	FName GETag;

public:
	USimpleAbilityGameplayEffect();

public:

	FORCEINLINE FName GetGameplayEffectTag() const { return GETag; }
};
