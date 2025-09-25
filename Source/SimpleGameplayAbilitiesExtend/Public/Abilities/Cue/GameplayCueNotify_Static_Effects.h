//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GameplayCueNotify_Static_Effects.generated.h"

class UParticleSystem;
class UNiagaraSystem;
class AHitCollision;
/**
 * 
 */
UCLASS()
class SIMPLEGAMEPLAYABILITIESEXTEND_API UGameplayCueNotify_Static_Effects : public UGameplayCueNotify_Static
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GA")
	UParticleSystem *EmitterTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GA")
	UNiagaraSystem* NiagaraTemplate;

	//需要特效的生命值名字
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GA")
	FName DurationName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GA")
	bool bAttach;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GA", meta = (EditCondition = "bAttach"))
	FName AttachPointName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GA", meta = (EditCondition = "bAttach"))
	TEnumAsByte<EAttachLocation::Type> AttachLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GA")
	FVector PositionOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GA")
	FRotator RotatorOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GA")
	TSubclassOf<AActor> HitCollisionClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GA")
	FVector CollisionPositionOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GA")
	FRotator CollisionRotatorOffset;
public:
	UGameplayCueNotify_Static_Effects();

	virtual void HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters);
};
