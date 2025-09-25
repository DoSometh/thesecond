//Copyright (C) RenZhai.2022.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Abilities/SimpleAbilitySystemComponent.h"
#include "Abilities/SimpleGameplayAbility.h"
//#include "SimpleComboType.h"
#include "SimpleFightComponent.generated.h"

struct SIMPLEGAMEPLAYABILITIESEXTEND_API FSimpleGameplayAbilitySpecHandleInfo
{
	//针对服务器使用
	FGameplayAbilitySpecHandle Handle;

	//针对客户端使用
	TSubclassOf<UGameplayAbility> AbilityClass;
};

UCLASS()
class SIMPLEGAMEPLAYABILITIESEXTEND_API USimpleFightComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	TWeakObjectPtr<USimpleAbilitySystemComponent> AbilitySystemComponent;

public:
	USimpleFightComponent();

	//添加能力
	UFUNCTION(BlueprintCallable, Category = "Fight")
	virtual FGameplayTag AddGameplayAbility(const TSubclassOf<UGameplayAbility>& InNewAbility);

	//移除能力
	UFUNCTION(BlueprintCallable, Category = "Fight")
	virtual void RemoveGameplayAbility(const FGameplayTag& InKey);

	//技能释放
	UFUNCTION(BlueprintCallable, Category = "Fight")
	virtual bool ExecuteGameplayAbility(const FGameplayTag& InName);

	//执行效果 比如buff
	UFUNCTION(BlueprintCallable, Category = "Fight")
	virtual void ExecuteGameplayEffect(const TSubclassOf<UGameplayEffect>& InGameplayEffect, int32 InCharacterLevel = 1);

	//移除效果 移除buff
	UFUNCTION(BlueprintCallable, Category = "Fight")
	virtual void DeactivationGameplayEffect(TSubclassOf<UGameplayEffect> InGameplayEffect);

	//技能是否在使用中
	UFUNCTION(BlueprintCallable, Category = "Fight")
	virtual bool IsUsingSkills(const FGameplayTag& InTag);

public:
	//只针对添加标签
	UFUNCTION(BlueprintCallable, Category = "Fight")
	void AddGameplyEffectTag(const FGameplayTag& InTag);

	//移除标签
	UFUNCTION(BlueprintCallable, Category = "Fight")
	void RemoveGameplyEffectTag(const FGameplayTag& InTag);

public:
	//获取技能标签名字
	UFUNCTION(BlueprintCallable, Category = "Fight")
	void GetSkillTagsNames(TArray<FName>& OutNames);

	//获取技能标签
	UFUNCTION(BlueprintCallable, Category = "Fight")
	void GetSkillTagsNameTag(TArray<FGameplayTag>& OutNames);

	//是否存在当前标签
	UFUNCTION(BlueprintPure, Category = "Fight")
	bool IsExitNameTag(const FGameplayTag &InTag) const;

public:
	UFUNCTION(BlueprintCallable, Category = "Fight")
	USimpleGameplayAbility* GetGameplayAbilityActiveTagBySkill();

	//获取默认的CDO
	UFUNCTION(BlueprintCallable, Category = "Fight")
	USimpleGameplayAbility* GetGameplayAbility(const FGameplayTag& InKey);

	//获取正在执行的 只针对服务器
	UFUNCTION(BlueprintCallable, Category = "Fight")
	USimpleGameplayAbility* GetExecuteGameplayAbility(const FGameplayTag& InKey);

public:
	//是否在天上
	UFUNCTION(BlueprintCallable, Category = "Fight")
	bool IsAir() const;

	UFUNCTION(BlueprintCallable, Category = "Fight")
	static FGameplayTag NameToGameTag(FName InTag);

public:
	//void Press(const FGameplayTag& InSlot);
	//
	//void Released(const FGameplayTag& InSlot);
	//
	//void Reset();

public:
	
	//角色拥有的技能
public:
	//FGameplayAbilitySpecHandle AddSkill(const FGameplayTag& InTags);
	//FGameplayAbilitySpecHandle AddComboAttacks(const FGameplayTag& InTags);

	//技能装备
public:
	//bool AddSkillSlot(int32 InSlot, const FName& InTag);
	//bool AddSkillSlot(int32 InSlot, const FMMOARPGSkillSlot& InSkillSlot);
	//bool RemoveSkillSlot(int32 InSlot, const FName& InTag);
public:

protected:
	//尝试激活
	bool TryActivateAbility(const FGameplayTag& InTagName, const TMap<FGameplayTag, FSimpleGameplayAbilitySpecHandleInfo>& InMap);

	//void RegisterComboAttack(const TArray<FGameplayTag>& InTags);

public:
	FORCEINLINE USimpleAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent.Get();}

public:
	//FSimpleComboCheck* GetSimpleComboInfo(const FGameplayTag& InKey);
	//FContinuousReleaseSpell* GetContinuousReleaseSpell();

public:
	//保留
	void UpdateLevel(float InLevel, TSubclassOf<UGameplayEffect> InNewReward);

	//保留
	virtual void RewardEffect(float InNewLevel, TSubclassOf<UGameplayEffect> InNewReward, TFunction<void()> InFun);

	//针对技能的具体添加
protected:
	//添加技能
	FSimpleGameplayAbilitySpecHandleInfo AddAbility(const TSubclassOf<UGameplayAbility> &InNewAbility);

	//移除技能
	void ClearAbility(const FSimpleGameplayAbilitySpecHandleInfo& InHanle);

protected:
	//bool ComboAttackContains(const FGameplayTag& InTage);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

protected:
	//void RegisterComboAttack(const FGameplayTag& Key);
	//void UnregisterComboAttack(const FGameplayTag &Key);

protected:
	TMap<FGameplayTag, FSimpleGameplayAbilitySpecHandleInfo> Skills;
};
