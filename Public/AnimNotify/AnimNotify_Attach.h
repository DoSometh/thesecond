//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Core/SimpleCombatCore.h"
#include "SimpleComboType.h"
#include "AnimNotify_Attach.generated.h"

UCLASS(meta = (DisplayName = "Attach"))
class SIMPLECOMBAT_API UAnimNotify_Attach : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_Attach();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,const FAnimNotifyEventReference& EventReference) override;

protected:
	//是否是自己
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attach")
	bool bReverseAddition;

	//类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attach")
	TSubclassOf<AActor> ActorClass;

	//查找方式
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attach")
	FName SubTag;

	//附加的SocketName
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attach")
	FName AttachSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attach")
	EAttachmentRule LocationRule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attach")
	EAttachmentRule RotationRule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attach")
	EAttachmentRule ScaleRule;

	//是否焊接
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attach")
	bool bInWeldSimulatedBodies;
};