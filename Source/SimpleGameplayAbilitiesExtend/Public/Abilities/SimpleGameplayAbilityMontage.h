//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "Abilities/SimpleGameplayAbility.h"
#include "Abilities/SimpleGameplayAbilityType.h"
#include "SimpleGameplayAbilityMontage.generated.h"

class UAbilityTask_PlayMontageAndWait;
class UAnimMontage;

UCLASS()
class SIMPLEGAMEPLAYABILITIESEXTEND_API USimpleGameplayAbilityMontage : public USimpleGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = MontageAbility)
	TObjectPtr<UAnimMontage> MontageToPlay;

	UPROPERTY(EditDefaultsOnly, Category = MontageAbility)
	bool bRandomMontageToPlay;

	//固定播放 需要继承 ISimpleGameplayAbilitiesExtendInterface 重写 GetGameplayAbilitiesMontageSections 指定播放哪个动画
	UPROPERTY(EditDefaultsOnly, Category = MontageAbility)
	bool bFixedMontageToPlay;

public:
	USimpleGameplayAbilityMontage();

public:
	int32 GetCompositeSectionsNumber();

public:

	UFUNCTION(BlueprintCallable, Category = "MMOARPGGameplayAbility|Tasks", meta = (DisplayName = "PlayMontageAndWait"))
		UAbilityTask_PNAWDamageEvent* CreatePlayMontageAndWaitProxy(
			FName TaskInstanceName,
			UAnimMontage* InMontageToPlay, 
			float Rate = 1.f, 
			FName StartSection = NAME_None,
			bool bStopWhenAbilityEnds = true,
			float AnimRootMotionTranslationScale = 1.f,
			float StartTimeSeconds = 0.f);

	UFUNCTION(BlueprintCallable, Category = "MMOARPGGameplayAbility|Tasks")
		UAbilityTask_PlayMontageAndWait *PlayMontage(FName StartSection = NAME_None);

private:
	UPROPERTY()
	UAbilityTask_PNAWDamageEvent* InWait;
};