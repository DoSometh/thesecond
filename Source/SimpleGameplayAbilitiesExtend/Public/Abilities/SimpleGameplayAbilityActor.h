//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "Abilities/SimpleGameplayAbility.h"
#include "Abilities/SimpleGameplayAbilityType.h"
#include "SimpleGameplayAbilityActor.generated.h"

class UAbilityTask_PlayMontageAndWait;
class UAnimMontage;

UCLASS()
class SIMPLEGAMEPLAYABILITIESEXTEND_API USimpleGameplayAbilityActor : public USimpleGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = MontageAbility)
	TSubclassOf<AActor> ActorToPlay;

public:
	USimpleGameplayAbilityActor();
};