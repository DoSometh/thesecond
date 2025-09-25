//Copyright (C) RenZhai.2022.All Rights Reserved.
#include "Abilities/Skill/Core/GameplayAbility_Skill.h"
#include "GameFramework/Character.h"
#include "Abilities/GameplayAbilityTypes.h"

void UGameplayAbility_Skill::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGameplayAbility_Skill::OnCompleted()
{
	Super::OnCompleted();

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);

	if (GetActorInfo().OwnerActor.IsValid())
	{
		if (ACharacter* InCharacter = Cast<ACharacter>(GetActorInfo().OwnerActor.Get()))
		{
			InCharacter->StopAnimMontage();
		}
	}
}

void UGameplayAbility_Skill::OnBlendOut()
{
	Super::OnBlendOut();

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGameplayAbility_Skill::OnInterrupted()
{
	Super::OnInterrupted();

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGameplayAbility_Skill::OnCancelled()
{
	Super::OnCancelled();

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}