//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_ContinuousSpell.generated.h"

/**
 * 
 */

//该标签必须用在蒙太奇动画上 否则无效
UCLASS(meta = (DisplayName = "ContinuousSpell"))
class SIMPLECOMBAT_API UAnimNotifyState_ContinuousSpell : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UAnimNotifyState_ContinuousSpell();

public:
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference);
};
