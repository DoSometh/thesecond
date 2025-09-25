//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "SimpleGameplayAbilityType.generated.h"

UENUM(BlueprintType)
enum class EGameplayEffectUseType :uint8
{
	RELEASE_TARGET_COLLISION		UMETA(DisplayName = "Release to Taget after collision"),//碰撞后释放buff
	RELEASE_OWN_COLLISION			UMETA(DisplayName = "Release to own after collision"),//碰撞后释放buff
};

USTRUCT(BlueprintType)
struct SIMPLEGAMEPLAYABILITIESEXTEND_API FSimpleGameplayEffect
{
	GENERATED_BODY()

public:
	FSimpleGameplayEffect();

	//被动buff类型 是释放到目标还是自己
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MMOARPGGameplayEffect)
	EGameplayEffectUseType GameplayEffectUseType;

	//buff类型的类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MMOARPGGameplayEffect)
	TSubclassOf<UGameplayEffect> EffectClass;
};

USTRUCT(BlueprintType)
struct SIMPLEGAMEPLAYABILITIESEXTEND_API FSimpleGameplayEffects
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffects)
	TArray<FSimpleGameplayEffect> GameplayEffects;
};

USTRUCT(BlueprintType)
struct SIMPLEGAMEPLAYABILITIESEXTEND_API FSimpleGameplayEffectSpec
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffects)
	FGameplayAbilityTargetDataHandle TargetHandleData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffects)
	TArray<FGameplayEffectSpecHandle> TargetEffectSpecs;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWaitSimpleForDamageEventDelegate, FGameplayTag, EventTag, FGameplayEventData, EventData);