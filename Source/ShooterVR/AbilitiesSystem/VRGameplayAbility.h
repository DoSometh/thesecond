#pragma once

#include "Abilities/Skill/Core/GameplayAbility_Skill.h"
#include "VRGameplayAbility.generated.h"

UCLASS()
class SHOOTERVR_API UVRGameplayAbility : public UGameplayAbility_Skill
{
	GENERATED_BODY()

public:
	UVRGameplayAbility();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
};