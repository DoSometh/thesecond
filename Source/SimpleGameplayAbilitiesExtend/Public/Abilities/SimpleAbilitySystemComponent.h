//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "AbilitySystemComponent.h"
#include "SimpleAbilitySystemComponent.generated.h"


UCLASS()
class SIMPLEGAMEPLAYABILITIESEXTEND_API USimpleAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	USimpleAbilitySystemComponent();

	static USimpleAbilitySystemComponent* GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent = false);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

	virtual void TickASC(float DeltaTime);

public:
	void SetCurrentActiveSkillTags(FGameplayTagContainer& InGameplayTagContainer) { CurrentActiveSkillTags = InGameplayTagContainer; }

	const FGameplayTagContainer* GetCurrentActiveSkillTags()const { return &CurrentActiveSkillTags; }

	void ResetCurrentActiveSkillTags();

	bool IsActiveGameplayEffectTags(const FGameplayTag &InTag);

protected:

	virtual void InitializeComponent();

protected:
	UPROPERTY()
	FGameplayTagContainer CurrentActiveSkillTags;

	UPROPERTY()
	float CurrentTime;
};