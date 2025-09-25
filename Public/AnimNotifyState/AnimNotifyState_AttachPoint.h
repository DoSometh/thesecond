//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_AttachPoint.generated.h"

class ACharacter;
/**
 * 快速与目标缩短距离
 */
UCLASS(meta = (DisplayName = "AttachPoint"))
class SIMPLECOMBAT_API UAnimNotifyState_AttachPoint : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UAnimNotifyState_AttachPoint();

	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference);

public:
	//离目标距离是多少
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotifyState_AttachPoint")
	float Distance;

	//视野角度 触发
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotifyState_AttachPoint")
	float Angle;

	//身份标识
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotifyState_AttachPoint")
	FName AttachPointTag;
};
