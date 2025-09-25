//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h"
#include "AnimNotifyState_CheckGrab.generated.h"

UCLASS(meta = (DisplayName = "CheckGrab"))
class SIMPLECOMBAT_API UAnimNotifyState_CheckGrab : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UAnimNotifyState_CheckGrab();

public:
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference);

public:
	ACharacter* GetGarbCharacter(USkeletalMeshComponent* MeshComp, USkeletalMeshComponent *&InBindMesh) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	FName GrabSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	TEnumAsByte<ETraceTypeQuery> TypeQuery;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	float Distance;

	//结束后是否停止动画
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	bool bEndStopMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	bool bDrawDebug;

	//次级模型名字
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	FName SubMeshTagName;
};