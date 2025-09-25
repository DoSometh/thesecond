//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_Death.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Death"))
class SIMPLECOMBAT_API UAnimNotify_Death : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_Death();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,const FAnimNotifyEventReference& EventReference) override;

public:
	bool IsBoneBroken(USkeletalMeshComponent* MeshComp, FName BoneName) const;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Target")
	bool bSimulation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Target")
	bool bEnableLiftTime;

	//How long will it be destroyed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Target", meta = (EditCondition = "bEnableLiftTime"))
	float LifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Face Target")
	TArray<FName> ExcludeBoneName;
};
