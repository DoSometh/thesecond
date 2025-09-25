#include "FightComponent.h"
#include "../../AbilitiesSystem/VRAbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

void UFightComponent::BeginPlay()
{
	Super::BeginPlay();

	if (IAbilitySystemInterface* InAbilitySystemInterface = GetOwner<IAbilitySystemInterface>())
	{
		AbilitySystemComponent = Cast<UVRAbilitySystemComponent>(InAbilitySystemInterface->GetAbilitySystemComponent());
	}
}

void UFightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UFightComponent::UnregisterGameplayAbility(const FGameplayAbilitySpecHandle& InHandle)
{
	if (InHandle.IsValid() && AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->ClearAbility(InHandle);
		return true;
	}

	return false;
}

FGameplayAbilitySpecHandle UFightComponent::RegisterGameplayAbility(const TSubclassOf<UGameplayAbility>& InGameplayAbility)
{
	if (IsValid(InGameplayAbility) && AbilitySystemComponent.IsValid())
	{
		return AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(InGameplayAbility));
	}

	return FGameplayAbilitySpecHandle();
}

bool UFightComponent::ExecuteGameplayAbility(const FGameplayAbilitySpecHandle& InHandle)
{
	if (InHandle.IsValid())
	{
		return AbilitySystemComponent->TryActivateAbility(InHandle);
	}

	return false;
}

void UFightComponent::ExecuteGameplayEffect(const TSubclassOf<UGameplayEffect>& InGameplayEffect)
{
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(GetOwner());

	FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
		InGameplayEffect,
		1.f,
		EffectContext);

	if (EffectSpecHandle.IsValid())
	{
		FActiveGameplayEffectHandle EffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
			*EffectSpecHandle.Data.Get(),
			AbilitySystemComponent.Get());
	}
}