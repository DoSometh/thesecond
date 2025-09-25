//Copyright (C) RenZhai.2022.All Rights Reserved.
#include "Abilities/SimpleGameplayAbilityMontage.h"
#include "Abilities/AbilityTask/AbilityTask_PMAWDamageEvent.h"
#include "Abilities/SimpleAbilitySystemComponent.h"
#include "Interface/ISimpleGameplayAbilitiesExtendInterface.h"

USimpleGameplayAbilityMontage::USimpleGameplayAbilityMontage()
{
	bRandomMontageToPlay = false;
	bFixedMontageToPlay = false;
}

UAbilityTask_PNAWDamageEvent* USimpleGameplayAbilityMontage::CreatePlayMontageAndWaitProxy(
	FName TaskInstanceName, 
	UAnimMontage* InMontageToPlay,
	float Rate, 
	FName StartSection,
	bool bStopWhenAbilityEnds,
	float AnimRootMotionTranslationScale, 
	float StartTimeSeconds)
{
	InWait = UAbilityTask_PNAWDamageEvent::CreatePNAWDamageEventProxy(
		this,
		TaskInstanceName,
		InMontageToPlay,
		AbilityTags,
		Rate,
		StartSection,
		bStopWhenAbilityEnds,
		AnimRootMotionTranslationScale);
	if (InWait)
	{
		InWait->OnBlendOut.AddDynamic(this, &USimpleGameplayAbility::OnBlendOut);
		InWait->OnCompleted.AddDynamic(this, &USimpleGameplayAbility::OnCompleted);
		InWait->OnInterrupted.AddDynamic(this, &USimpleGameplayAbility::OnInterrupted);
		InWait->OnCancelled.AddDynamic(this, &USimpleGameplayAbility::OnCancelled);
		InWait->DamageEventReceived.AddDynamic(this, &USimpleGameplayAbility::OnDamageGameplayEvent);

		//激活
		InWait->Activate();

		return InWait;
	}

	return nullptr;
}

int32 USimpleGameplayAbilityMontage::GetCompositeSectionsNumber()
{
	if (MontageToPlay)
	{
		return MontageToPlay->CompositeSections.Num();
	}

	return 0;
}

UAbilityTask_PlayMontageAndWait* USimpleGameplayAbilityMontage::PlayMontage(FName StartSection)
{
	if (bRandomMontageToPlay)
	{
		int32 CompositeSectionsNumber = GetCompositeSectionsNumber();
		if (CompositeSectionsNumber > 1)
		{
			StartSection = *FString::FromInt(FMath::RandRange(0, GetCompositeSectionsNumber() - 1));
		}
		else if (CompositeSectionsNumber == 1)
		{
			StartSection = TEXT("0");
		}
	}
	else
	{
		if (bFixedMontageToPlay)
		{
			if (const FGameplayAbilityActorInfo* ActorInfo = GetCurrentActorInfo())
			{
				if (ISimpleGameplayAbilitiesExtendInterface* InExtendInterface = Cast<ISimpleGameplayAbilitiesExtendInterface>(ActorInfo->OwnerActor))
				{
					int32 MontageSections = InExtendInterface->GetGameplayAbilitiesMontageSections(AbilityTags.First());
					if (MontageSections != INDEX_NONE)
					{
						StartSection = *FString::FromInt(MontageSections);
					}
				}
			}
		}	
	}

	float RateScale = 1.f;

	//获取播放速率
	for (auto &Tmp : MontageToPlay->CompositeSections)
	{
		if (Tmp.SectionName == StartSection)
		{
			if (const UAnimSequenceBase* InSequenceBase = Tmp.GetLinkedSequence())
			{
				RateScale = InSequenceBase->RateScale;
			}

			break;
		}		
	}

	if (!bCustom)
	{
		return CreatePlayMontageAndWaitProxy(NAME_None, MontageToPlay, RateScale, StartSection);
	}

	if (UAbilityTask_PlayMontageAndWait *InPAW = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this,
		NAME_None,
		MontageToPlay,
		RateScale,
		StartSection,
		true))
	{
		if (Execute())
		{
			InPAW->Activate();
			
			return InPAW;
		}
	}
	
	return NULL;
}