//Copyright (C) RenZhai.2022.All Rights Reserved.

#include "Abilities/SimpleGameplayAbility.h"
#include "Abilities/SimpleAbilitySystemComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

USimpleGameplayAbility::USimpleGameplayAbility()
{
	bCustom = false;
	LiftTime = 8.f;

	bEnableOnlyTimerRemoveEffectTag = false;
}

void USimpleGameplayAbility::OnDamageGameplayEvent(
	FGameplayTag InGameplayTag, 
	FGameplayEventData Payload)
{
	if (FSimpleGameplayEffects* InEffect = EffectMap.Find(InGameplayTag))
	{
		FSimpleGameplayEffectSpec GameplayEffectSpec;
		{
			FGameplayAbilityTargetData_ActorArray* NewTargetData_ActorArray = new FGameplayAbilityTargetData_ActorArray();
		
			for (auto& Tmp : InEffect->GameplayEffects)
			{
				if (Tmp.GameplayEffectUseType == EGameplayEffectUseType::RELEASE_OWN_COLLISION)
				{
					//为了兼容更高版本
					const AActor *TmpActor = Payload.Instigator;

					NewTargetData_ActorArray->TargetActorArray.Add(const_cast<AActor*>(TmpActor));
					GameplayEffectSpec.TargetHandleData.Add(NewTargetData_ActorArray);
				}
				else if (Tmp.GameplayEffectUseType == EGameplayEffectUseType::RELEASE_TARGET_COLLISION)
				{
					//为了兼容更高版本
					const AActor* TmpActor = Payload.Target;

					NewTargetData_ActorArray->TargetActorArray.Add(const_cast<AActor*>(TmpActor));
					GameplayEffectSpec.TargetHandleData.Add(NewTargetData_ActorArray);
				}
				else
				{
					break;
				}

				FGameplayEffectSpecHandle NewHandle =
					GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(Tmp.EffectClass, 1,
						MakeEffectContext(CurrentSpecHandle, CurrentActorInfo));

				if (NewHandle.IsValid())
				{
					FGameplayAbilitySpec* AbilitySpec =
						GetAbilitySystemComponentFromActorInfo()->FindAbilitySpecFromHandle(CurrentSpecHandle);

					ApplyAbilityTagsToGameplayEffectSpec(*NewHandle.Data.Get(), AbilitySpec);

					if (AbilitySpec)
					{
						NewHandle.Data->SetByCallerTagMagnitudes = AbilitySpec->SetByCallerTagMagnitudes;

						GameplayEffectSpec.TargetEffectSpecs.Add(NewHandle);
					}
				}				
			}
		}

		for (auto &Tmp : GameplayEffectSpec.TargetEffectSpecs)
		{
			K2_ApplyGameplayEffectSpecToTarget(Tmp, GameplayEffectSpec.TargetHandleData);
		}
	}

	if (bCustom)
	{
		//按照时间计算器来移除EffectTag效果
		if (!bEnableOnlyTimerRemoveEffectTag)
		{	
			//播放GAS完成
			OnCompleted();
		}	
	}
}

void USimpleGameplayAbility::RegisterActiveSkillTag()
{
	if (USimpleAbilitySystemComponent* InSimpleCompent = Cast<USimpleAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent))
	{
		InSimpleCompent->SetCurrentActiveSkillTags(AbilityTags);
	}
}

void USimpleGameplayAbility::UnregisterActiveSkillTag()
{
	if (USimpleAbilitySystemComponent* InSimpleCompent = Cast<USimpleAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent))
	{
		InSimpleCompent->ResetCurrentActiveSkillTags();
	}
}

void USimpleGameplayAbility::EndAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, 
	bool bReplicateEndAbility, bool bWasCancelled)
{	
	//移除代理
	RemoveDamageEventHandle();

	UnregisterActiveSkillTag();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void USimpleGameplayAbility::OnDamageGameplayBindEvent(FGameplayTag InGameplayTag, const FGameplayEventData* Payload)
{
	FGameplayEventData EventData = *Payload;
	EventData.EventTag = InGameplayTag;

	OnDamageGameplayEvent(InGameplayTag,EventData);
}

bool USimpleGameplayAbility::CalculationAbilityTimer()
{
	if (const FGameplayAbilityActorInfo* ActorInfo = GetCurrentActorInfo())
	{
		if (ActorInfo->AbilitySystemComponent.IsValid())
		{
			ActorInfo->AbilitySystemComponent->GetWorld()->GetTimerManager().SetTimer(
				TimerHandle,
				this,
				&USimpleGameplayAbility::RemoveDamageEventHandle,LiftTime);

			return true;
		}
	}

	return false;
}

void USimpleGameplayAbility::RemoveDamageEventHandle()
{
	if (const FGameplayAbilityActorInfo* ActorInfo = GetCurrentActorInfo())
	{
		if (ActorInfo->AbilitySystemComponent.IsValid())
		{
			if (ActorInfo->AbilitySystemComponent->GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
			{
				//清除时间计算器
				ActorInfo->AbilitySystemComponent->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			}

			ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(
				AbilityTags,
				DamageEventHandle);
		}
	}
}

bool USimpleGameplayAbility::Execute()
{
	const FGameplayAbilityActorInfo* ActorInfo = GetCurrentActorInfo();
	if (ActorInfo->AbilitySystemComponent.IsValid())
	{
		if (CalculationAbilityTimer())
		{
			DamageEventHandle = ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(
				FGameplayTagContainer(),
				FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &USimpleGameplayAbility::OnDamageGameplayBindEvent));

			return true;
		}
	}

	return false;
}

float USimpleGameplayAbility::CostValue(const FString& InCostName, float InLevel)
{
	if (UGameplayEffect *InCostBuff = GetCostGameplayEffect())
	{
		for (auto&Tmp : InCostBuff->Modifiers)
		{
			if (Tmp.Attribute.GetName() == InCostName)
			{
				float InValue = 0.f;
				if (Tmp.ModifierMagnitude.GetStaticMagnitudeIfPossible(InLevel,InValue))
				{
					return FMath::Abs(InValue);
				}
			}
		}
	}

	return 0.0f;
}

void USimpleGameplayAbility::OnCompleted()
{
	K2_OnCompleted();
}

void USimpleGameplayAbility::OnBlendOut()
{
	K2_OnBlendOut();
}

void USimpleGameplayAbility::OnInterrupted()
{
	K2_OnInterrupted();
}

void USimpleGameplayAbility::OnCancelled()
{
	K2_OnCancelled();
}
