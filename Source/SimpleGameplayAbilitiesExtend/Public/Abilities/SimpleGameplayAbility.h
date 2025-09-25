//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "Abilities/GameplayAbility.h"
#include "Abilities/SimpleGameplayAbilityType.h"
#include "SimpleGameplayAbility.generated.h"

UCLASS()
class SIMPLEGAMEPLAYABILITIESEXTEND_API USimpleGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = MontageAbility)
	bool bCustom;

	UPROPERTY(EditDefaultsOnly, Category = MontageAbility, meta = (EditCondition = "bRemoteSkill"))
	float LiftTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffects)
	TMap<FGameplayTag,FSimpleGameplayEffects> EffectMap;

	UPROPERTY(EditDefaultsOnly, Category = GameplayAbility)
	bool bEnableOnlyTimerRemoveEffectTag;

public:
	USimpleGameplayAbility();

	UFUNCTION()
	virtual void OnCompleted();

	UFUNCTION()
	virtual void OnBlendOut();

	UFUNCTION()
	virtual void OnInterrupted();

	UFUNCTION()
	virtual void OnCancelled();

	UFUNCTION()
	virtual	void OnDamageGameplayEvent(FGameplayTag InGameplayTag,FGameplayEventData Payload);

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

	void OnDamageGameplayBindEvent(FGameplayTag InGameplayTag,const FGameplayEventData *Payload);

	bool CalculationAbilityTimer();
	void RemoveDamageEventHandle();

public:
	virtual bool Execute();

public:
	float CostValue(const FString & InCostName,float InLevel);

public:
	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnCancelled", meta = (ScriptName = "OnCancelled"))
	void K2_OnCancelled();

	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnInterrupted", meta = (ScriptName = "OnInterrupted"))
	void K2_OnInterrupted();
	
	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnBlendOut", meta = (ScriptName = "OnBlendOut"))
	void K2_OnBlendOut();
	
	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnCompleted", meta = (ScriptName = "OnCompleted"))
	void K2_OnCompleted();

protected:
	void RegisterActiveSkillTag();
	void UnregisterActiveSkillTag();

private:
	FDelegateHandle DamageEventHandle;
	FTimerHandle TimerHandle;
};