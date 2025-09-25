//Copyright (C) RenZhai.2022.All Rights Reserved.
#include "Abilities/SimpleAbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"

USimpleAbilitySystemComponent::USimpleAbilitySystemComponent()
{
	//PrimaryComponentTick.bCanEverTick = true;

	CurrentTime = 0.f;
}

USimpleAbilitySystemComponent* USimpleAbilitySystemComponent::GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent)
{
	return Cast<USimpleAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor, LookForComponent));
}

void USimpleAbilitySystemComponent::TickASC(float DeltaTime)
{
	CurrentTime += DeltaTime;
	if (CurrentTime >= 5.f)
	{
		CurrentTime = 0.f;
		BlockedAbilityTags.Reset();
	}
}

void USimpleAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void USimpleAbilitySystemComponent::ResetCurrentActiveSkillTags()
{
	CurrentActiveSkillTags.Reset();
}

void USimpleAbilitySystemComponent::InitializeComponent()
{
	Super::InitializeComponent();


}

bool USimpleAbilitySystemComponent::IsActiveGameplayEffectTags(const FGameplayTag& InTag)
{
	TArray<FActiveGameplayEffectHandle> GAHandle = ActiveGameplayEffects.GetAllActiveEffectHandles();
	for (auto& Tmp : GAHandle)
	{
		if (FActiveGameplayEffect* InActiveGameplayEffect = ActiveGameplayEffects.GetActiveGameplayEffect(Tmp))
		{
			if (const UGameplayEffect* InDef = InActiveGameplayEffect->Spec.Def)
			{
				if (InDef->InheritableGameplayEffectTags.CombinedTags.HasTag(InTag))
				{
					return true;
				}
			}
		}
	}

	return false;
}
