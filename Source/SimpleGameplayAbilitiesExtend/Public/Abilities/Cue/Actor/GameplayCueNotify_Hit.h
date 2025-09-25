//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "GameplayCueNotify_Hit.generated.h"

class UParticleSystem;
class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class SIMPLEGAMEPLAYABILITIESEXTEND_API AGameplayCueNotify_Hit : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()
public:
	AGameplayCueNotify_Hit();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GA Hit")
	UParticleSystem *HitEmitterTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GA Hit")
	UNiagaraSystem* HitNiagaraTemplate;

public:
	virtual void HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters);
};
