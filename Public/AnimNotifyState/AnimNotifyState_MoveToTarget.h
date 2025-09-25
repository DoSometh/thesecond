//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SimpleComboType.h"
#include "AnimNotifyState_MoveToTarget.generated.h"

class ACharacter;
/**
 * 
 */
UCLASS(meta = (DisplayName = "MoveToTarget"))
class SIMPLECOMBAT_API UAnimNotifyState_MoveToTarget : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UAnimNotifyState_MoveToTarget();

	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Target")
	float OverlappingDistance;
};
