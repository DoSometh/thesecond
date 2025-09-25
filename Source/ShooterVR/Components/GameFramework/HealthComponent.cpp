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
	AFrameworkCharacterBase* InstigatorPawn,//ʩ����
	AActor* DamageCauser,//ʵ������˺����� �������ӵ�Ҳ������ʩ����
	const FGameplayTagContainer& InTags,//��Ӧ���Buffer�ı�ǩ
	float InNewValue)//�˺�ֵ
{
	if (FrameworkCharacterBase.IsValid())
	{
		if (IsDie())
		{
			//�����Է�
			//InstigatorPawn

			FrameworkCharacterBase->PlayDie();
		}
		else
		{
			FrameworkCharacterBase->PlayHit();
		}
	}
}
