//Copyright (C) RenZhai.2022.All Rights Reserved.
#include "Abilities/Skill/Core/GameplayAbility_Effect.h"
#include "GameFramework/Character.h"
#include "Abilities/GameplayAbilityTypes.h"

void UGameplayAbility_Effect::OnCompleted()
{
	Super::OnCompleted();

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGameplayAbility_Effect::OnBlendOut()
{
	Super::OnBlendOut();

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGameplayAbility_Effect::OnInterrupted()
{
	Super::OnInterrupted();

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGameplayAbility_Effect::OnCancelled()
{
	Super::OnCancelled();

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}