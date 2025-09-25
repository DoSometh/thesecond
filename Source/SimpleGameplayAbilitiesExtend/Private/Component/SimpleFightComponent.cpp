//Copyright (C) RenZhai.2022.All Rights Reserved.

#include "Component/SimpleFightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"

USimpleFightComponent::USimpleFightComponent()
{

}

bool USimpleFightComponent::IsUsingSkills(const FGameplayTag& InTag)
{
	if (AbilitySystemComponent.IsValid())
	{
		if (const auto* CurrentActiveSkillTag = AbilitySystemComponent->GetCurrentActiveSkillTags())
		{
			return CurrentActiveSkillTag->HasAny(FGameplayTagContainer(InTag));
		}
	}

	return false;
}

//bool USimpleFightComponent::AddSkillSlot(int32 InSlot, const FName& InTag)
//{
//	//添加到我们的实际技能表
//	FMMOARPGSkillSlot SkillSlot;
//	EMMOARPGSkillType SkillType = (EMMOARPGSkillType)InSlot;
//
//	if (SkillType == EMMOARPGSkillType::COMBO_GROUND_SKILL || //添加combo连击
//		SkillType == EMMOARPGSkillType::COMBO_AIR_SKILL)
//	{
//		SkillSlot.Handle = AddComboAttacks(InTag);
//
//		//注册连击
//		RegisterComboAttack(InTag);
//	}
//	else //添加技能
//	{
//		SkillSlot.Handle = AddSkill(InTag);
//	}
//
//	SkillSlot.SkillName = InTag;
//
//	//技能节点里面
//	return AddSkillSlot(InSlot, SkillSlot);
//}

//bool USimpleFightComponent::RemoveSkillSlot(int32 InSlot, const FName& InTag)
//{
//	//移除原来的
//	RemoveSkillSlot(InSlot);
//
//	//添加设定的
//	return AddSkillSlot(InSlot, InTag);
//}
////
//bool USimpleFightComponent::RemoveSkillSlot(int32 InSlot)
//{
//	if (SkillSlots.Contains(InSlot))
//	{
//		EMMOARPGSkillType SkillType = (EMMOARPGSkillType)InSlot;
//		if (SkillType == EMMOARPGSkillType::COMBO_GROUND_SKILL || //添加combo连击
//			SkillType == EMMOARPGSkillType::COMBO_AIR_SKILL)
//		{
//			RemoveComboAttacks(SkillSlots[InSlot].SkillName);
//
//			//注册连击
//			UnregisterComboAttack(SkillSlots[InSlot].SkillName);
//		}
//		else //添加技能
//		{
//			//先移除真实技能
//			RemoveSkill(SkillSlots[InSlot].SkillName);
//		}
//
//		//再移除技能节点
//		SkillSlots[InSlot] = FMMOARPGSkillSlot();
//
//		return true;
//	}
//
//	return false;
//}

//
//void USimpleFightComponent::Press(const FGameplayTag &InTag)
//{
//	for (auto& Tmp : ComboAttack)
//	{
//		if (IsAir())
//		{
//			if (Tmp.ComboKey == InTag.GetTagName())
//			{
//				Tmp.Press();
//				break;
//			}
//		}
//		else
//		{
//			if (Tmp.ComboKey == InTag.GetTagName())
//			{
//				Tmp.Press();
//				break;
//			}
//		}
//	}
//}
//
//void USimpleFightComponent::Released(const FGameplayTag &InTag)
//{
//	for (auto& Tmp : ComboAttack)
//	{
//		if (GEngine)
//		{
//			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("%i"), Tmp.ComboIndex));
//		}
//
//		if (Tmp.ComboKey == InTag.GetTagName())
//		{
//			Tmp.Released();
//			break;
//		}
//	}
//}
//
//FSimpleComboCheck* USimpleFightComponent::GetSimpleComboInfo(const FGameplayTag& InKey)
//{
//	return ComboAttack.FindByPredicate(
//	[&](const FSimpleComboCheck& InComboCheck)
//	{
//		return InComboCheck.ComboKey == InKey;
//	});
//}
//
//FContinuousReleaseSpell* USimpleFightComponent::GetContinuousReleaseSpell()
//{
//	return &ContinuousReleaseSpell;
//}

void USimpleFightComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
//
//void USimpleFightComponent::Reset()
//{
//	//Combo连击
//	for (auto& Tmp : ComboAttack)
//	{
//		Tmp.Reset();
//	}
//
//	//持续施法
//	ContinuousReleaseSpell.Reset();
//}

//FGameplayAbilitySpecHandle USimpleFightComponent::AddSkill(const FGameplayTag& InTags)
//{
//	/*if (AMMOARPGGameState* InGameState = GetWorld()->GetGameState<AMMOARPGGameState>())
//	{
//		if (FCharacterSkillTable* InSkillTable = InGameState->GetCharacterSkillTable(InTags, MMOARPGCharacterBase->GetID()))
//		{
//			if (!Skills.Contains(InTags))
//			{
//				Skills.Add(InTags, AddAbility(InSkillTable->GameplayAbility));
//				return Skills[InTags];
//			}
//		}
//	}*/
//
//	return FGameplayAbilitySpecHandle();
//}
//
//FGameplayAbilitySpecHandle USimpleFightComponent::AddComboAttacks(const FGameplayTag& InTags)
//{
//	//if (AMMOARPGGameState* InGameState = GetWorld()->GetGameState<AMMOARPGGameState>())
//	//{
//	//	if (FCharacterSkillTable* InSkillTable = InGameState->GetCharacterSkillTable(InTags, MMOARPGCharacterBase->GetID()))
//	//	{
//	//		if (!ComboAttacks.Contains(InTags))
//	//		{
//	//			ComboAttacks.Add(InTags, AddAbility(InSkillTable->GameplayAbility));
//	//			return ComboAttacks[InTags];
//	//		}
//	//	}
//	//}
//
//	return FGameplayAbilitySpecHandle();
//}

//
//void USimpleFightComponent::RemoveComboAttacks(const FName& InTags)
//{
//	if (ComboAttacks.Contains(InTags))
//	{
//		ClearAbility(ComboAttacks[InTags]);
//
//		//移除我们的Map
//		ComboAttacks.Remove(InTags);
//	}
//}

void USimpleFightComponent::AddGameplyEffectTag(const FGameplayTag& InTag)
{
	AbilitySystemComponent->AddLooseGameplayTag(InTag);
	AbilitySystemComponent->SetTagMapCount(InTag, 1);
}

void USimpleFightComponent::RemoveGameplyEffectTag(const FGameplayTag& InTag)
{
	AbilitySystemComponent->RemoveLooseGameplayTag(InTag);
}

bool USimpleFightComponent::TryActivateAbility(const FGameplayTag& InTagName, const TMap<FGameplayTag, FSimpleGameplayAbilitySpecHandleInfo>& InMap)
{
	if (AbilitySystemComponent.IsValid())
	{
		if (const auto* Handle = InMap.Find(InTagName))
		{
			if (GetWorld()->IsNetMode(ENetMode::NM_Client))
			{
				//客户端执行
				return AbilitySystemComponent->TryActivateAbilityByClass(Handle->AbilityClass);
			}

			return AbilitySystemComponent->TryActivateAbility(Handle->Handle);		
		}
	}

	return false;
}

void USimpleFightComponent::ExecuteGameplayEffect(const TSubclassOf<UGameplayEffect>& InGameplayEffect,int32 InCharacterLevel)
{
	if (!InGameplayEffect)
	{
		return;
	}

	if (!GetWorld()->IsNetMode(ENetMode::NM_Client))
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(GetOwner());

		FGameplayEffectSpecHandle EffectSpecHandle =
			AbilitySystemComponent->MakeOutgoingSpec(InGameplayEffect,
				InCharacterLevel,
				EffectContext);
		if (EffectSpecHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
				*EffectSpecHandle.Data.Get(),
				AbilitySystemComponent.Get());
		}
	}
}

void USimpleFightComponent::DeactivationGameplayEffect(TSubclassOf<UGameplayEffect> InGameplayEffect)
{
	if (!GetWorld()->IsNetMode(ENetMode::NM_Client))
	{
		AbilitySystemComponent->RemoveActiveGameplayEffectBySourceEffect(
			InGameplayEffect, AbilitySystemComponent.Get());
	}
}

bool USimpleFightComponent::ExecuteGameplayAbility(const FGameplayTag &InName)
{
	return TryActivateAbility(InName, Skills);
}

FGameplayTag USimpleFightComponent::AddGameplayAbility(const TSubclassOf<UGameplayAbility>& InNewAbility)
{
	FGameplayTag GameTag;
	if (InNewAbility)
	{
		if (UGameplayAbility* InGameplayAbility = Cast<UGameplayAbility>(InNewAbility->GetDefaultObject()))
		{
			GameTag = InGameplayAbility->AbilityTags.First();

			Skills.Add(GameTag, AddAbility(InNewAbility));
		}
	}

	//if (AMMOARPGGameState* InGameState = GetWorld()->GetGameState<AMMOARPGGameState>())
	//{
	//	//添加固有技能
	//	if (FCharacterSkillTable* InSkillTable = InGameState->GetCharacterSkillTable(InKey, MMOARPGCharacterBase->GetID()))
	//	{
	//		Skills.Add(InKey, AddAbility(InSkillTable->GameplayAbility));
	//	}
	//}

	return GameTag;
}

void USimpleFightComponent::RemoveGameplayAbility(const FGameplayTag& InKey)
{
	if (FSimpleGameplayAbilitySpecHandleInfo *InHandle = Skills.Find(InKey))
	{
		ClearAbility(*InHandle);

		Skills.Remove(InKey);
	}
}

void USimpleFightComponent::BeginPlay()
{
	Super::BeginPlay();

	if (IAbilitySystemInterface *InSystemInterface = Cast<IAbilitySystemInterface>(GetOwner()))
	{
		AbilitySystemComponent = Cast<USimpleAbilitySystemComponent>(InSystemInterface->GetAbilitySystemComponent());

		if (AbilitySystemComponent.IsValid())
		{
			//服务器注册 客户端不能注册
			AbilitySystemComponent->InitAbilityActorInfo(GetOwner(), GetOwner());
		}
	}
}

FSimpleGameplayAbilitySpecHandleInfo USimpleFightComponent::AddAbility(const TSubclassOf<UGameplayAbility>& InNewAbility)
{
	FSimpleGameplayAbilitySpecHandleInfo HandleInfo;

	if (IsValid(InNewAbility) && AbilitySystemComponent.IsValid())
	{
		if (GetWorld()->IsNetMode(ENetMode::NM_Client))
		{
			HandleInfo.AbilityClass = InNewAbility;
		}
		else
		{
			HandleInfo.Handle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(InNewAbility));
		}
	}

	return HandleInfo;
}

void USimpleFightComponent::ClearAbility(const FSimpleGameplayAbilitySpecHandleInfo& InHanle)
{
	if (!GetWorld()->IsNetMode(ENetMode::NM_Client))
	{
		//只针对服务器有效
		AbilitySystemComponent->ClearAbility(InHanle.Handle);
	}
}
//
//bool USimpleFightComponent::ComboAttackContains(const FGameplayTag& InTage)
//{
//	if (ComboAttack.FindByPredicate([&](const FSimpleComboCheck& InComboAttack)
//		{
//			return InComboAttack.ComboKey == InTage.GetTagName();
//		}))
//	{
//		return true;
//	}
//
//	return false;
//}

USimpleGameplayAbility* USimpleFightComponent::GetGameplayAbilityActiveTagBySkill()
{
	if (const FGameplayTagContainer* InTagContainer = AbilitySystemComponent->GetCurrentActiveSkillTags())
	{
		return GetGameplayAbility(InTagContainer->First());
	}

	return nullptr;
}

USimpleGameplayAbility* USimpleFightComponent::GetGameplayAbility(const FGameplayTag& InKey)
{
	if (const auto* InHandle = Skills.Find(InKey))
	{
		if (AbilitySystemComponent.IsValid())
		{
			if (GetWorld()->IsNetMode(ENetMode::NM_Client))
			{
				if (InHandle->AbilityClass)
				{
					return Cast<USimpleGameplayAbility>(InHandle->AbilityClass->GetDefaultObject());
				}
			}
			else
			{
				if (FGameplayAbilitySpec* Spec = AbilitySystemComponent->FindAbilitySpecFromHandle(InHandle->Handle))
				{
					return Cast<USimpleGameplayAbility>(Spec->Ability);
				}
			}
		}
	}

	return nullptr;
}

USimpleGameplayAbility* USimpleFightComponent::GetExecuteGameplayAbility(const FGameplayTag& InKey)
{
	UGameplayAbility* InPrimaryAbilityInstance = nullptr;

	if (const auto* InHandle = Skills.Find(InKey))
	{
		if (FGameplayAbilitySpec* Spec = AbilitySystemComponent->FindAbilitySpecFromHandle(InHandle->Handle))
		{
			switch (Spec->Ability->GetInstancingPolicy())
			{
				case EGameplayAbilityInstancingPolicy::InstancedPerActor:
				{
					UGameplayAbility* PrimaryAbility = Spec->GetPrimaryInstance();
					if (PrimaryAbility)
					{
						InPrimaryAbilityInstance = PrimaryAbility;
					}
				
					break;
				}
				case EGameplayAbilityInstancingPolicy::InstancedPerExecution:
				{
					if (Spec->Ability->GetReplicationPolicy() == EGameplayAbilityReplicationPolicy::ReplicateYes)
					{
						if (Spec->ReplicatedInstances.Num() > 0)
						{
							InPrimaryAbilityInstance = Spec->ReplicatedInstances[Spec->ReplicatedInstances.Num() - 1];
						}
					}
					else
					{
						if (Spec->NonReplicatedInstances.Num() > 0)
						{
							InPrimaryAbilityInstance = Spec->NonReplicatedInstances[Spec->NonReplicatedInstances.Num() - 1];
						}
					}
					break;
				}
				case EGameplayAbilityInstancingPolicy::NonInstanced:
				{
					// 技能通过CDO执行
					InPrimaryAbilityInstance = Spec->Ability;
				
					break;
				}
			}
		}
	}

	return Cast<USimpleGameplayAbility>(InPrimaryAbilityInstance);
}

bool USimpleFightComponent::IsAir() const
{
	if (ACharacter *InCharacter = Cast<ACharacter>(GetOwner()))
	{
		if (UCharacterMovementComponent* InCharacterMovement = InCharacter->GetCharacterMovement())
		{
			return InCharacterMovement->IsFalling();
		}
	}

	return false;
}

FGameplayTag USimpleFightComponent::NameToGameTag(FName InTag)
{
	return FGameplayTag::RequestGameplayTag(InTag);
}

//void USimpleFightComponent::RegisterComboAttack(const TArray<FName>& InTags)
//{
//	for (auto& Tmp : InTags)
//	{
//		RegisterComboAttack(Tmp);
//	}
//}

void USimpleFightComponent::GetSkillTagsNameTag(TArray<FGameplayTag>& OutNames)
{
	Skills.GetKeys(OutNames);
}

bool USimpleFightComponent::IsExitNameTag(const FGameplayTag& InTag) const
{
	return Skills.Contains(InTag);
}

void USimpleFightComponent::GetSkillTagsNames(TArray<FName>& OutNames)
{
	TArray<FGameplayTag> OutTagNames;
	GetSkillTagsNameTag(OutTagNames);

	for (auto &Tmp : OutTagNames)
	{
		OutNames.Add(Tmp.GetTagName());
	}
}

//void USimpleFightComponent::GetComboAttackTagsName(TArray<FName>& OutNames)
//{
//	ComboAttacks.GetKeys(OutNames);
//}

void USimpleFightComponent::UpdateLevel(float InLevel, TSubclassOf<UGameplayEffect> InNewReward)
{
	if (AbilitySystemComponent.IsValid())
	{
		checkf(InNewReward, TEXT("This value needs to be configured in the blueprint."));

		AbilitySystemComponent->ApplyGameplayEffectToSelf(
			Cast<UGameplayEffect>(InNewReward->GetDefaultObject()),
			InLevel, AbilitySystemComponent->MakeEffectContext());
	}
}

void USimpleFightComponent::RewardEffect(
	float InNewLevel,
	TSubclassOf<UGameplayEffect> InNewReward, TFunction<void()> InFun)
{
	if (!InNewReward)
	{
		return;
	}

	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectToSelf(
			Cast<UGameplayEffect>(InNewReward->GetDefaultObject()),
			InNewLevel, AbilitySystemComponent->MakeEffectContext());

		InFun();
	}
}
//
//void USimpleFightComponent::RegisterComboAttack(const FGameplayTag& Key)
//{
//	if (!ComboAttackContains(Key))
//	{
//		FSimpleComboCheck& InComboAttack = ComboAttack.AddDefaulted_GetRef();
//
//		InComboAttack.Character = MMOARPGCharacterBase.Get();
//		InComboAttack.ComboKey = Key;
//		if (UMMOARPGGameplayAbility* GameplayAbility = GetGameplayAbilityByCombo(Key))
//		{
//			InComboAttack.MaxIndex = GameplayAbility->GetCompositeSectionsNumber();
//		}
//		else
//		{
//			InComboAttack.MaxIndex = 4;
//		}
//	}
//}
//
//void USimpleFightComponent::UnregisterComboAttack(const FGameplayTag& Key)
//{
//	if (ComboAttackContains(Key))
//	{
//		FSimpleComboCheck RemoveKey;
//		RemoveKey.ComboKey = Key.ToName();
//
//		ComboAttack.Remove(RemoveKey);
//	}
//}