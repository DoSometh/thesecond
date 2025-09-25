#pragma once
#include "CoreMinimal.h"
#include "Core/MotionComponent.h"
#include "FightComponent.generated.h"

class UVRAbilitySystemComponent;
class UGameplayAbility;
struct FGameplayAbilitySpecHandle;
class UGameplayEffect;

UCLASS()
class SHOOTERVR_API UFightComponent : public UMotionComponent
{
	GENERATED_BODY()
	UPROPERTY()
	TWeakObjectPtr<UVRAbilitySystemComponent> AbilitySystemComponent;

public:
	FGameplayAbilitySpecHandle RegisterGameplayAbility(const TSubclassOf<UGameplayAbility>& InGameplayAbility);
	bool UnregisterGameplayAbility(const FGameplayAbilitySpecHandle& InHandle);

	virtual bool ExecuteGameplayAbility(const FGameplayAbilitySpecHandle& InHandle);
	virtual void ExecuteGameplayEffect(const TSubclassOf<UGameplayEffect>& InGameplayEffect);
protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

};