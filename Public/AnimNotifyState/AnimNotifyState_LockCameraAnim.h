//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Camera/PlayerCameraManager.h"
#include "AnimNotifyState_LockCameraAnim.generated.h"

class ACharacter;

UENUM()
enum class ELockCameraAnimViewTargetBlendFunction : uint8
{
	/** Camera does a simple linear interpolation. */
	VTBlend_Linear,
	/** Camera has a slight ease in and ease out, but amount of ease cannot be tweaked. */
	VTBlend_Cubic,
	/** Camera immediately accelerates, but smoothly decelerates into the target.  Ease amount controlled by BlendExp. */
	VTBlend_EaseIn,
	/** Camera smoothly accelerates, but does not decelerate into the target.  Ease amount controlled by BlendExp. */
	VTBlend_EaseOut,
	/** Camera smoothly accelerates and decelerates.  Ease amount controlled by BlendExp. */
	VTBlend_EaseInOut,
	/** The game's camera system has already performed the blending. Engine should not blend at all */
	VTBlend_PreBlended,
	VTBlend_MAX,
};

UCLASS(meta = (DisplayName = "LockCameraAnim"))
class SIMPLECOMBAT_API UAnimNotifyState_LockCameraAnim : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UAnimNotifyState_LockCameraAnim();

	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LockCameraAnim")
	FName CurrentCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LockCameraAnim")
	float BlendValue;

	//是否要锁摄像机 将摄像机锁定到角色
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LockCameraAnim")
	bool bLockCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LockCameraAnim")
	bool bReturn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LockCameraAnim")
	ELockCameraAnimViewTargetBlendFunction TargetBlendFunction;

protected:
	AActor* GetBlendCamera(USkeletalMeshComponent* MeshComp, const FName& InCameraString);
	void CameraBlend(USkeletalMeshComponent* MeshComp, const FName& InCameraString, float InBlendValue);

protected:
	AActor* Camera;
};
