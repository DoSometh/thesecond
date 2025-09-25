//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "SimpleComboType.h"
#include "SimpleCombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI,meta = (CannotImplementInterfaceInBlueprint))
class USimpleComboInterface : public UInterface
{
	GENERATED_BODY()
};

class SIMPLECOMBAT_API ISimpleComboInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	ISimpleComboInterface();

	UFUNCTION(BlueprintCallable, Category="Combat")
	virtual void AnimSignal(int32 InSignal) {}

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual bool ComboAttack(int32 InKey) { return false; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual bool ComboAttackByTag(const FName &InKey) { return false; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual bool ComboAttackByGameplayTag(const FGameplayTag& InKey) { return false; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual AActor* GetTarget() const { return NULL; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual float GetCharacterLevel() { return 1; }

	//被抓起
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void CaughtUP(AActor *InWho) { }

	//被扔掉
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void Throw(AActor* InWho){}

	//提供 UAnimNotifyState_AttachSocketLerp
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual AActor* AttachSocketLerpActor() const { return nullptr; }

	//针对更新吸附点准备
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void Update_AttachPoint(const FSimpleAttachPointInfo &InValue, FName InTag,bool bEnd);

	virtual struct FSimpleComboCheck* GetSimpleComboInfo(int32 InKey) { return NULL; }
	virtual struct FSimpleComboCheck* GetSimpleComboInfo(const FName &InKey) { return NULL; }
	virtual struct FSimpleComboCheck* GetSimpleComboInfo(const FGameplayTag& InKey) { return NULL; }

	//准备丢弃
	virtual struct FContinuousReleaseSpell* GetContinuousReleaseSpell() { return NULL; }

public:
	//需要上层执行tick操作
	void TickDrive(float InNewTime);

public:
	FSimpleAttachPointInfo FindAttachPointInfo(FName InName);

private:
	TMap<FName, FSimpleAttachPointInfo> AttachPointAlpha;
	FRWLock RWLock;
};
