// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleModularActor.h"
#include "AbilitySystemInterface.h"
#include "../../AbilitiesSystem/VRAbilitySystemComponent.h"
#include "CombatInterface/SimpleAttackInterface.h"
#include "VRWeaponBase.generated.h"

class USimpleGrabComponent;
class USkeletalMeshComponent;
class UFightComponent;
class UVRAttributeSetBase;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class SHOOTERVR_API AVRWeaponBase 
	: public ASimpleModularActor	
	,public IAbilitySystemInterface
	, public ISimpleAttackInterface
{
	friend class AShooterVRGameStateBase;

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USimpleGrabComponent> GrabComponent;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	//战斗逻辑都在里面
	UPROPERTY(Category = Ability, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFightComponent> FightComponent;

	//GAS
	UPROPERTY(Category = Ability, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UVRAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	int32 ID;

public:
	AVRWeaponBase();

public:
	FGameplayAbilitySpecHandle RegisterGameplayAbility(const TSubclassOf<UGameplayAbility>& InGameplayAbility);
	bool UnregisterGameplayAbility(const FGameplayAbilitySpecHandle& InHandle);

	bool ExecuteGameplayAbility(const FGameplayAbilitySpecHandle& InHandle);
	void ExecuteGameplayEffect(const TSubclassOf<UGameplayEffect>& InGameplayEffect);

public:
	virtual void PlayAnimMontage(UAnimMontage* InMontage);
	virtual void StopAnimMontage();
public:
	USimpleGrabComponent* GetGrabComponent() const { return GrabComponent; }
	AActor* GetAttachObject() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	UFUNCTION(BlueprintPure, Category = "Weapon|Grab")
	FORCEINLINE bool IsHeld() const;

	UFUNCTION(BlueprintPure, Category = "Weapon|ID")
	FORCEINLINE int32 GetID() const { return ID; }

	UFUNCTION(BlueprintPure, Category = "Weapon|Attribute")
	virtual UVRAttributeSetBase* GetAttribute() const { return NULL; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void RegistrationAttribute();

public:
	virtual APawn* GetCaster();

protected:
	UFUNCTION()
	virtual void Grab();

	UFUNCTION()
	virtual void Release();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
