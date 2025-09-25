#include "VRGameplayAbility.h"

UVRGameplayAbility::UVRGameplayAbility()
{

}

void UVRGameplayAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}
	if (PlayMontage(TEXT("Default")))
	{
		RegisterActiveSkillTag();
	}
}
