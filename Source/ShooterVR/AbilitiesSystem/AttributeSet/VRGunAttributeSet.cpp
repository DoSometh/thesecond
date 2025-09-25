// Fill out your copyright notice in the Description page of Project Settings.
#include "VRGunAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "../../DataTable/Attribute/Weapon/GunAttributeTable.h"

UVRGunAttributeSet::UVRGunAttributeSet()
	:Super()
	,BulletsNumber(0)
	,MaxBulletsNumber(10)
{

}

void UVRGunAttributeSet::OnRep_BulletsNumber(const FGameplayAttributeData& OldValue)
{
	CHECK_OWNING_ASC_GAMEPLAYATTRIBUTE_REPNOTIFY(
		UVRGunAttributeSet, BulletsNumber, OldValue,
		TEXT("OnRep_BulletsNumber Error"));
}

void UVRGunAttributeSet::OnRep_MaxBulletsNumber(const FGameplayAttributeData& OldValue)
{
	CHECK_OWNING_ASC_GAMEPLAYATTRIBUTE_REPNOTIFY(
		UVRGunAttributeSet, MaxBulletsNumber, OldValue,
		TEXT("OnRep_MaxBulletsNumber Error"));
}

void UVRGunAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UVRGunAttributeSet, BulletsNumber);
	DOREPLIFETIME(UVRGunAttributeSet, MaxBulletsNumber);
};

void UVRGunAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

bool UVRGunAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UVRGunAttributeSet::RegistrationProperties(const FAttributeDataTableBase* InData)
{
	Super::RegistrationProperties(InData);

	const FGunAttributeTable *InTable = (const FGunAttributeTable*)InData;

	RegistrationParam(MaxBulletsNumber, InTable->BulletsNumber);
}