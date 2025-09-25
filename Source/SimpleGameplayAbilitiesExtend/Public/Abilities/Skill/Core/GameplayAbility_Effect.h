//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Abilities/SimpleGameplayAbility.h"
#include "GameplayAbility_Effect.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEGAMEPLAYABILITIESEXTEND_API UGameplayAbility_Effect : public USimpleGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void OnCompleted();

	virtual void OnBlendOut();

	virtual void OnInterrupted();

	virtual void OnCancelled();
};
