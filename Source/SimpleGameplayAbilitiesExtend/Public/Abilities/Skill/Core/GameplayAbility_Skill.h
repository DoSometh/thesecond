//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Abilities/SimpleGameplayAbilityMontage.h"
#include "GameplayAbility_Skill.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEGAMEPLAYABILITIESEXTEND_API UGameplayAbility_Skill : public USimpleGameplayAbilityMontage
{
	GENERATED_BODY()

public:
	virtual void OnCompleted();

	virtual void OnBlendOut();

	virtual void OnInterrupted();

	virtual void OnCancelled();

public:
	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility, bool bWasCancelled);
};
