//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/SimpleGameplayAbilityType.h" 
#include "AbilityTask_PMAWDamageEvent.generated.h"

/** Ability task to simply play a montage. Many games will want to make a modified version of this task that looks for game-specific events */
UCLASS()
class SIMPLEGAMEPLAYABILITIESEXTEND_API UAbilityTask_PNAWDamageEvent : public UAbilityTask_PlayMontageAndWait
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FWaitSimpleForDamageEventDelegate DamageEventReceived;

public:
	UAbilityTask_PNAWDamageEvent(const FObjectInitializer& ObjectInitializer);

	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;

	static UAbilityTask_PNAWDamageEvent* CreatePNAWDamageEventProxy(
			UGameplayAbility* OwningAbility,
			FName TaskInstanceName,
			UAnimMontage* MontageToPlay, 
			FGameplayTagContainer InEventTags,
			float Rate = 1.f,
			FName StartSection = NAME_None, 
			bool bStopWhenAbilityEnds = true, 
			float AnimRootMotionTranslationScale = 1.f,
			float StartTimeSeconds = 0.f);
private:
	void OnDamageGameplayEvent(FGameplayTag InGameplayTag, const FGameplayEventData* Payload);

private:
	UPROPERTY()
	FGameplayTagContainer EventTags;

private:
	FDelegateHandle DamageEventHandle;
};