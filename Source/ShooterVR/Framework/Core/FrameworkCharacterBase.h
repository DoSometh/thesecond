// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleModularCharacter.h"
#include "AbilitySystemInterface.h"
#include "ShooterVR/ShooterVRType.h"
#include "FrameworkCharacterBase.generated.h"

class UFightComponent;
class UVRAbilitySystemComponent;
class UAbilitySystemComponent;
struct FGameplayAbilitySpecHandle;
class UGameplayAbility;
class UVRShooterAttributeSet;
class UHealthComponent;
class UGameplayEffect;

UCLASS()
class SHOOTERVR_API AFrameworkCharacterBase :
	public ASimpleModularCharacter,
	public IAbilitySystemInterface
{
	friend class AShooterVRGameStateBase;

	GENERATED_BODY()

	//战斗逻辑都在里面
	UPROPERTY(Category = Ability, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFightComponent> FightComponent;

	UPROPERTY(Category = Ability, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;

	//GAS
	UPROPERTY(Category = Ability, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UVRAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(Category = Attribute, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UVRShooterAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	int32 ID;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	EVRHitType MainHitType;
	
	UPROPERTY(BlueprintReadOnly, Category = Hit, meta = (AllowPrivateAccess = "true"))
	FHitResult HitResult;
public:
	// Sets default values for this character's properties
	AFrameworkCharacterBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FGameplayAbilitySpecHandle RegisterGameplayAbility(const TSubclassOf<UGameplayAbility>& InGameplayAbility);
	bool UnregisterGameplayAbility(const FGameplayAbilitySpecHandle& InHandle);

	virtual bool ExecuteGameplayAbility(const FGameplayAbilitySpecHandle& InHandle);
	virtual void ExecuteGameplayEffect(const TSubclassOf<UGameplayEffect>& InGameplayEffect);

public:
	virtual void PlayAnimMontage(UAnimMontage* InMontage);
	virtual void StopAnimMontage();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

public:
	void RegistrationAttribute();

public:
	bool IsDie()const;

public:
	virtual void HandleHealth(AFrameworkCharacterBase* InstigatorPawn,
		AActor* DamageCauser, const struct FGameplayTagContainer& InTags,
		float InNewValue);

public:
	virtual void PlayDie();
	virtual void PlayHit();

	UFUNCTION(BlueprintImplementableEvent, Category = "Character|Fight", meta = (DisplayName = "PlayHit"))
	void BP_PlayHit();

	UFUNCTION(BlueprintImplementableEvent, Category = "Character|Fight", meta = (DisplayName = "PlayDie"))
	void BP_PlayDie();

public:
	UFUNCTION(BlueprintCallable, Category = "FrameworkCharacter|HitResult")
	void SetHitResult(const FHitResult& InHitResult) { HitResult = InHitResult; }

	UFUNCTION(BlueprintCallable, Category = "FrameworkCharacter|HitResult")
	void ClearHitResult();

	UFUNCTION(BlueprintCallable, Category = "FrameworkCharacter|Hit")
	void PlayHitSound(EVRHitType InType);

	UFUNCTION(BlueprintCallable, Category = "FrameworkCharacter|Hit")
	void PlayHitEffect(EVRHitType InType);

	UFUNCTION(BlueprintCallable, Category = "FrameworkCharacter|Hit")
	void PlayHitScar(EVRHitType InType);

	UFUNCTION(BlueprintCallable, Category = "FrameworkCharacter|Hit")
	bool PlayBoneImpulse();
public:
	UFUNCTION(BlueprintPure, Category = "FrameworkCharacter|Fight")
	FORCEINLINE UFightComponent* GetFightComponent() const { return FightComponent; }

	UFUNCTION(BlueprintPure, Category = "FrameworkCharacter|ID")
	FORCEINLINE int32 GetID() const { return ID; }

	UFUNCTION(BlueprintPure, Category = "FrameworkCharacter|Attribute")
	virtual UVRShooterAttributeSet* GetAttribute() const { return AttributeSet; }
};