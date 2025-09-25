//Copyright (C) RenZhai.2022.All Rights Reserved.
#include "AnimNotifyState/AnimNotifyState_CheckCombo.h"
#include "SimpleComboType.h"
#include "CombatInterface/SimpleCombatInterface.h"
#include "Components/SkeletalMeshComponent.h"

#if PLATFORM_WINDOWS
#pragma optimize("",off) 
#endif

void UAnimNotifyState_CheckCombo::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (MeshComp->GetOuter() && MeshComp->GetOuter()->GetWorld())
	{
		if (!MeshComp->GetOuter()->GetWorld()->IsNetMode(ENetMode::NM_Client))
		{
			if (ISimpleComboInterface* InCharacter = Cast<ISimpleComboInterface>(MeshComp->GetOuter()))
			{
				if (InCharacter->GetSimpleComboInfo(ComboTagKey))
				{
					InCharacter->GetSimpleComboInfo(ComboTagKey)->bShortPress = false;
					InCharacter->GetSimpleComboInfo(ComboTagKey)->UpdateComboIndex();
				}
			}
		}
	}
}

void UAnimNotifyState_CheckCombo::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime,EventReference);


}

void UAnimNotifyState_CheckCombo::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation,EventReference);

	if (MeshComp->GetOuter() && MeshComp->GetOuter()->GetWorld())
	{
		if (!MeshComp->GetOuter()->GetWorld()->IsNetMode(ENetMode::NM_Client))
		{
			if (ISimpleComboInterface* InCharacter = Cast<ISimpleComboInterface>(MeshComp->GetOuter()))
			{
				if (InCharacter->GetSimpleComboInfo(ComboTagKey) && 
					(InCharacter->GetSimpleComboInfo(ComboTagKey)->bLongPress 
						|| InCharacter->GetSimpleComboInfo(ComboTagKey)->bShortPress))
				{
					InCharacter->ComboAttackByGameplayTag(ComboTagKey);
				}
				else
				{
					if (FSimpleComboCheck *InComboCheck = InCharacter->GetSimpleComboInfo(ComboTagKey))
					{
						InComboCheck->Reset();
					}
				}
			}
		}
	}
}

#if PLATFORM_WINDOWS
#pragma optimize("",on) 
#endif