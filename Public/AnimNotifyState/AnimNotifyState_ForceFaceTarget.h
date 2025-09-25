//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_ForceFaceTarget.generated.h"

class ACharacter;
/**
 * 
 */
UCLASS(meta = (DisplayName = "ForceFaceTarget"))
class SIMPLECOMBAT_API UAnimNotifyState_ForceFaceTarget : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UAnimNotifyState_ForceFaceTarget();

	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Target")
	bool bYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Target")
	bool bPitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Target")
	bool bRoll;
};
