//Copyright (C) RenZhai.2022.All Rights Reserved.
#include "Abilities/SimpleGameplayAbilityActor.h"
#include "Abilities/AbilityTask/AbilityTask_PMAWDamageEvent.h"
#include "Abilities/SimpleAbilitySystemComponent.h"

USimpleGameplayAbilityActor::USimpleGameplayAbilityActor()
	:Super()
{
	bEnableOnlyTimerRemoveEffectTag = true;
}