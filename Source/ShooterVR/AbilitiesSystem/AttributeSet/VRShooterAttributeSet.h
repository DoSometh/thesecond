// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/VRAttributeSetBase.h"
#include "VRShooterAttributeSet.generated.h"

class AFrameworkCharacterBase;
/**
 * 
 */
UCLASS()
class SHOOTERVR_API UVRShooterAttributeSet : public UVRAttributeSetBase
{
	GENERATED_BODY()

public:
	UVRShooterAttributeSet();

public:
	UPROPERTY(BlueprintReadOnly, Category = "Character Attribute", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	PROPERTY_FUNCTION_REGISTRATION(UVRShooterAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Character Attribute", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	PROPERTY_FUNCTION_REGISTRATION(UVRShooterAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Character Attribute", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	PROPERTY_FUNCTION_REGISTRATION(UVRShooterAttributeSet, Mana)

	UPROPERTY(BlueprintReadOnly, Category = "Character Attribute", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	PROPERTY_FUNCTION_REGISTRATION(UVRShooterAttributeSet, MaxMana)

	UPROPERTY(BlueprintReadOnly, Category = "Character Attribute", ReplicatedUsing = OnRep_PhysicsDefense)
	FGameplayAttributeData PhysicsDefense;
	PROPERTY_FUNCTION_REGISTRATION(UVRShooterAttributeSet, PhysicsDefense)

	UPROPERTY(BlueprintReadOnly, Category = "Character Attribute", ReplicatedUsing = OnRep_MagicDefense)
	FGameplayAttributeData MagicDefense;
	PROPERTY_FUNCTION_REGISTRATION(UVRShooterAttributeSet, MagicDefense)

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	virtual void RegistrationProperties(const FAttributeDataTableBase* InData);

public:
	virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected:
	void GetSourceCharacterAndSourceActor(UAbilitySystemComponent* SourceAbilitySystemComponent, AActor*& InSourceActor, AFrameworkCharacterBase*& InSourceCharacter);

protected:
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_PhysicsDefense(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MagicDefense(const FGameplayAttributeData& OldValue);
};
