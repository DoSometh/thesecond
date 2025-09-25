// Copyright (C) RenZhai.2025.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Engine/EngineTypes.h"
#include "AnimNotifyState_MovementMode.generated.h"

UCLASS(meta = (DisplayName = "EnableMovementMode"))
class SIMPLECOMBAT_API UAnimNotifyState_MovementMode : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UAnimNotifyState_MovementMode();

public:
	//希望进入过程后状态
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	TEnumAsByte<EMovementMode> MovementMode;

	//结束后希望恢复的状态 需要开启 bLeaveItAsItIs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	TEnumAsByte<EMovementMode> EndMovementMode;

	//进入前是什么状态 结束后就是什么状态
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	bool bLeaveItAsItIs;

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

private:
	//作为保存
	UPROPERTY()
	TEnumAsByte<EMovementMode> CharacterMovementMode;
};
