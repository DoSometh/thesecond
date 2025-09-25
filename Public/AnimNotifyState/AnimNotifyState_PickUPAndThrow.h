//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Hit/Core/ComboSkillHitCollision.h"
#include "AnimNotifyState_PickUPAndThrow.generated.h"

class ACharacter;

UCLASS(meta = (DisplayName = "PickUP And Throw"))
class SIMPLECOMBAT_API UAnimNotifyState_PickUPAndThrow : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UAnimNotifyState_PickUPAndThrow();

	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference);

public:
	//抛的对象
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	TSubclassOf<AHitCollision> ActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	float LiftTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	FName BindSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	bool bHoming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	bool bSelfRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	int32 HitID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	FGameplayTag GASTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	TArray<FGameplayTag> BuffTags;
};
