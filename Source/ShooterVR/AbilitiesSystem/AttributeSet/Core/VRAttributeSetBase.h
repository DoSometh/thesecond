// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Abilities/SimpleGameplayAbilityMacros.h"
#include "VRAttributeSetBase.generated.h"

struct FAttributeDataTableBase;
/**
 * 
 */
UCLASS()
class SHOOTERVR_API UVRAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

public:
	UVRAttributeSetBase();

public:
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Level)
	FGameplayAttributeData Level;
	PROPERTY_FUNCTION_REGISTRATION(UVRAttributeSetBase, Level)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_PhysicsAttack)
	FGameplayAttributeData PhysicsAttack;
	PROPERTY_FUNCTION_REGISTRATION(UVRAttributeSetBase, PhysicsAttack)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MagicAttack)
	FGameplayAttributeData MagicAttack;
	PROPERTY_FUNCTION_REGISTRATION(UVRAttributeSetBase, MagicAttack)

	//¡Ÿ ±¥Ê¥¢
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Damage)
	FGameplayAttributeData Damage;
	PROPERTY_FUNCTION_REGISTRATION(UVRAttributeSetBase, Damage)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_EmpiricalValue)
	FGameplayAttributeData EmpiricalValue;
	PROPERTY_FUNCTION_REGISTRATION(UVRAttributeSetBase, EmpiricalValue)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MaxEmpiricalValue)
	FGameplayAttributeData MaxEmpiricalValue;
	PROPERTY_FUNCTION_REGISTRATION(UVRAttributeSetBase, MaxEmpiricalValue)

public:
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

public:
	virtual void RegistrationProperties(const FAttributeDataTableBase* InData);

protected:
	void RegistrationParam(FGameplayAttributeData& InAttributeData, const float InValue);

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	virtual void OnRep_Level(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_PhysicsAttack(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MagicAttack(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Damage(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_EmpiricalValue(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxEmpiricalValue(const FGameplayAttributeData& OldValue);
};
