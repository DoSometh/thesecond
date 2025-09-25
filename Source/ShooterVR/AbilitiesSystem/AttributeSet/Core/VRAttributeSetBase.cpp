// Fill out your copyright notice in the Description page of Project Settings.
#include "VRAttributeSetBase.h"
#include "Net/UnrealNetwork.h"
#include "../../../DataTable/Core/AttributeDataTableBase.h"

UVRAttributeSetBase::UVRAttributeSetBase()
	: Super()
	, Level(1)
	, PhysicsAttack(10.f)
	, MagicAttack(10.f)
	, Damage(0.f)
	, EmpiricalValue(0.f)
	, MaxEmpiricalValue(100.f)
{

}

void UVRAttributeSetBase::OnRep_Level(const FGameplayAttributeData& OldValue)
{
	CHECK_OWNING_ASC_GAMEPLAYATTRIBUTE_REPNOTIFY(
		UVRAttributeSetBase, Level, OldValue,
		TEXT("OnRep_Level Error"));
}

void UVRAttributeSetBase::OnRep_PhysicsAttack(const FGameplayAttributeData& OldValue)
{
	CHECK_OWNING_ASC_GAMEPLAYATTRIBUTE_REPNOTIFY(
		UVRAttributeSetBase, PhysicsAttack, OldValue,
		TEXT("OnRep_PhysicsAttack Error"));
}

void UVRAttributeSetBase::OnRep_MagicAttack(const FGameplayAttributeData& OldValue)
{
	CHECK_OWNING_ASC_GAMEPLAYATTRIBUTE_REPNOTIFY(
		UVRAttributeSetBase, MagicAttack, OldValue,
		TEXT("OnRep_MagicAttack Error"));
}

void UVRAttributeSetBase::OnRep_Damage(const FGameplayAttributeData& OldValue)
{
	CHECK_OWNING_ASC_GAMEPLAYATTRIBUTE_REPNOTIFY(
		UVRAttributeSetBase, Damage, OldValue,
		TEXT("OnRep_Damage Error"));
}

void UVRAttributeSetBase::OnRep_EmpiricalValue(const FGameplayAttributeData& OldValue)
{
	CHECK_OWNING_ASC_GAMEPLAYATTRIBUTE_REPNOTIFY(
		UVRAttributeSetBase, EmpiricalValue, OldValue,
		TEXT("OnRep_EmpiricalValue Error"));
}

void UVRAttributeSetBase::OnRep_MaxEmpiricalValue(const FGameplayAttributeData& OldValue)
{
	CHECK_OWNING_ASC_GAMEPLAYATTRIBUTE_REPNOTIFY(
		UVRAttributeSetBase, MaxEmpiricalValue, OldValue,
		TEXT("OnRep_MaxEmpiricalValue Error"));
}

void UVRAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UVRAttributeSetBase::RegistrationProperties(const FAttributeDataTableBase* InData)
{
	RegistrationParam(PhysicsAttack, InData->PhysicsAttack);
	RegistrationParam(MagicAttack, InData->MagicAttack);
	RegistrationParam(MaxEmpiricalValue, InData->EmpiricalValue);
}

void UVRAttributeSetBase::RegistrationParam(FGameplayAttributeData& InAttributeData, const float InValue)
{
	InAttributeData.SetBaseValue(InValue);
	InAttributeData.SetCurrentValue(InValue);
}

bool UVRAttributeSetBase::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UVRAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UVRAttributeSetBase, Level);
	DOREPLIFETIME(UVRAttributeSetBase, PhysicsAttack);
	DOREPLIFETIME(UVRAttributeSetBase, MagicAttack);
	DOREPLIFETIME(UVRAttributeSetBase, EmpiricalValue);
	DOREPLIFETIME(UVRAttributeSetBase, MaxEmpiricalValue);
};