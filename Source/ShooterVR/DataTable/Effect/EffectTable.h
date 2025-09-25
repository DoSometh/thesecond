//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "../../ShooterVRType.h"
#include "EffectTable.generated.h"

class UNiagaraSystem;
class UParticleSystem;

USTRUCT(BlueprintType, Blueprintable)
struct FEffectTable :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FEffectTable();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Effect")
	EVRHitType HitType;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Effect")
	UNiagaraSystem* HitNiagara;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Effect")
	UParticleSystem* HitParticle;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Scar Effect")
	UMaterialInterface *Scar;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Scar Effect")
	FVector ScarSize;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Scar Effect")
	float ScarLifeSpan;
};