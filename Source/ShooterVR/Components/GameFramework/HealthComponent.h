//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Core/MotionComponent.h"
#include "HealthComponent.generated.h"

class UVRAbilitySystemComponent;
class UVRShooterAttributeSet;
class AFrameworkCharacterBase;
struct FGameplayTagContainer;

UCLASS()
class SHOOTERVR_API UHealthComponent : public UMotionComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TWeakObjectPtr<UVRAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	UVRShooterAttributeSet *AttributeSet;

	UPROPERTY()
	TWeakObjectPtr<AFrameworkCharacterBase> FrameworkCharacterBase;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

public:
	bool IsDie()const;

public:
	virtual void HandleHealth(AFrameworkCharacterBase* InstigatorPawn,
		AActor* DamageCauser, const struct FGameplayTagContainer& InTags,
		float InNewValue);
};