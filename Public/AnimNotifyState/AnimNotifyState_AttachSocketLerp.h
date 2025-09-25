//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SimpleComboType.h"
#include "AnimNotifyState_AttachSocketLerp.generated.h"

class ACharacter;
/**
 * 针对Socket 附加 具有插值
 */
UCLASS(meta = (DisplayName = "Attach Socket Lerp"))
class SIMPLECOMBAT_API UAnimNotifyState_AttachSocketLerp : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UAnimNotifyState_AttachSocketLerp();

	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotifyState_AttachPoint")
	FName SocketNameOriginal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotifyState_AttachPoint")
	FName SocketNameTarget;

	//mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotifyState_AttachPoint")
	FName MeshTag;
};
