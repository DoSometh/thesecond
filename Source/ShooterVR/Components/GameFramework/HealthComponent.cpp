#include "HealthComponent.h"
#include "../../AbilitiesSystem/VRAbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "../../AbilitiesSystem/AttributeSet/VRShooterAttributeSet.h"
#include "../../Framework/Core/FrameworkCharacterBase.h"

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	FrameworkCharacterBase = Cast<AFrameworkCharacterBase>(GetOwner());

	if (IAbilitySystemInterface* InAbilitySystemInterface = GetOwner<IAbilitySystemInterface>())
	{
		AbilitySystemComponent = Cast<UVRAbilitySystemComponent>(InAbilitySystemInterface->GetAbilitySystemComponent());
	}

	AttributeSet = const_cast<UVRShooterAttributeSet*>(AbilitySystemComponent->GetSet<UVRShooterAttributeSet>());
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UHealthComponent::IsDie() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetHealth() <= 0.f;
	}

	return false;
}

void UHealthComponent::HandleHealth(
	AFrameworkCharacterBase* InstigatorPawn,//施法者
	AActor* DamageCauser,//实际造成伤害对象 可能是子弹也可能是施法者
	const FGameplayTagContainer& InTags,//对应这个Buffer的标签
	float InNewValue)//伤害值
{
	if (FrameworkCharacterBase.IsValid())
	{
		if (IsDie())
		{
			//奖励对方
			//InstigatorPawn

			FrameworkCharacterBase->PlayDie();
		}
		else
		{
			FrameworkCharacterBase->PlayHit();
		}
	}
}
