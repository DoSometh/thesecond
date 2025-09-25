//Copyright (C) RenZhai.2022.All Rights Reserved.
#include "AnimNotifyState/AnimNotifyState_ContinuousSpell.h"
#include "SimpleComboType.h"
#include "CombatInterface/SimpleCombatInterface.h"
#include "CombatInterface/SimpleAttackInterface.h"
#include "GameFramework/Character.h"
#include "SimpleCombatBPLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"

UAnimNotifyState_ContinuousSpell::UAnimNotifyState_ContinuousSpell()
{

}

void UAnimNotifyState_ContinuousSpell::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (MeshComp->GetOuter() && MeshComp->GetOuter()->GetWorld())
	{
		if (ISimpleComboInterface* InCharacter = Cast<ISimpleComboInterface>(MeshComp->GetOuter()))
		{
			if (FContinuousReleaseSpell *InSpell = InCharacter->GetContinuousReleaseSpell())
			{
				if ( InSpell->IsStart() || 
					!InSpell->IsVaild() || 
					 InSpell->IsEnd() || 
					 !InSpell->IsLoop())
				{
					//进入下一个循环
					InSpell->ResetLoop();
				}
			}
		}	
	}
}

void UAnimNotifyState_ContinuousSpell::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime,EventReference);

	if (MeshComp->GetOuter() && MeshComp->GetOuter()->GetWorld())
	{
		if (UAnimInstance* InAnimInstance = MeshComp->GetAnimInstance())
		{
			if (ISimpleComboInterface* InCharacterInterface = Cast<ISimpleComboInterface>(MeshComp->GetOuter()))
			{
				if (FContinuousReleaseSpell* InSpell = InCharacterInterface->GetContinuousReleaseSpell())
				{
					if (ISimpleAttackInterface* InSimpleAttackInterface = Cast<ISimpleAttackInterface>(MeshComp->GetOuter()))
					{
						//如果不允许攻击 直接终止攻击
						if (!InSimpleAttackInterface->IsAllowAttack())
						{
							InSpell->ResetEnd();

							FName SectionName = InSpell->GetCurrentState();
							InAnimInstance->Montage_JumpToSection(SectionName);

							//释放掉
							InSpell->Released();
						}
					}
				}
			}
		}
	}
}

void UAnimNotifyState_ContinuousSpell::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation,EventReference);

	if (MeshComp->GetOuter() && MeshComp->GetOuter()->GetWorld())
	{	
		if (ISimpleComboInterface* InCharacterInterface = Cast<ISimpleComboInterface>(MeshComp->GetOuter()))
		{
			if (FContinuousReleaseSpell* InSpell = InCharacterInterface->GetContinuousReleaseSpell())
			{	
				if (UAnimInstance* InAnimInstance = MeshComp->GetAnimInstance())
				{
					FName SectionName = InSpell->GetCurrentState();
					if (InSpell->IsEnd())
					{
						InAnimInstance->Montage_JumpToSection(SectionName);

						//释放掉
						InSpell->Released();
					}
					else //可以切换各种各样的循环
					{
						InAnimInstance->Montage_JumpToSection(SectionName);
						InAnimInstance->Montage_SetNextSection(SectionName, SectionName);
					}
				}
			}
		}	
	}
}