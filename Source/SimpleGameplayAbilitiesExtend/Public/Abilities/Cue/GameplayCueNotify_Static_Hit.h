//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GameplayCueNotify_Static_Hit.generated.h"

class UParticleSystem;
class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class SIMPLEGAMEPLAYABILITIESEXTEND_API UGameplayCueNotify_Static_Hit : public UGameplayCueNotify_Static
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GA Hit")
	UParticleSystem *HitEmitterTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GA Hit")
	UNiagaraSystem* HitNiagaraTemplate;

public:
	virtual void HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters);
};
