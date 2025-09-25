// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/VRAttributeSetBase.h"
#include "VRGunAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERVR_API UVRGunAttributeSet : public UVRAttributeSetBase
{
	GENERATED_BODY()

public:
	UVRGunAttributeSet();

public:
	UPROPERTY(BlueprintReadOnly, Category = "Gun Attribute", ReplicatedUsing = OnRep_BulletsNumber)
	FGameplayAttributeData BulletsNumber;
	PROPERTY_FUNCTION_REGISTRATION(UVRGunAttributeSet, BulletsNumber)

	UPROPERTY(BlueprintReadOnly, Category = "Gun Attribute", ReplicatedUsing = OnRep_MaxBulletsNumber)
	FGameplayAttributeData MaxBulletsNumber;
	PROPERTY_FUNCTION_REGISTRATION(UVRGunAttributeSet, MaxBulletsNumber)

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	virtual void RegistrationProperties(const FAttributeDataTableBase* InData);

public:
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected:
	UFUNCTION()
	virtual void OnRep_BulletsNumber(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxBulletsNumber(const FGameplayAttributeData& OldValue);
};
