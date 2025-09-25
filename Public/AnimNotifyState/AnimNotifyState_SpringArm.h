//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SimpleComboType.h"
#include "AnimNotifyState_SpringArm.generated.h"

class ACharacter;
/**
 * 
 */
UCLASS(meta = (DisplayName = "SpringArm"))
class SIMPLECOMBAT_API UAnimNotifyState_SpringArm : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UAnimNotifyState_SpringArm();

	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpringArm")
	float CurrentArmLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpringArm")
	float TargetArmLength;
};
