//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Core/SimpleCombatCore.h"
#include "AnimNotify_Detach.generated.h"


UCLASS(meta = (DisplayName = "Detach"))
class SIMPLECOMBAT_API UAnimNotify_Detach : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_Detach();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attach")
	bool bReverseAddition;

	//类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	TSubclassOf<AActor> ActorClass;

	//查找方式
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detach")
	FName SubTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detach")
	bool bResetRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detach")
	bool bResetLocation;

	//相对
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComputerGraphics", meta = (EditCondition = "bResetRotation"))
	FRotator DetachRotation;

	//相对
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ComputerGraphics", meta = (EditCondition = "bResetLocation"))
	FVector DetachLocation;
};