//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_PlayAnimMontage.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "PlayAnimMontage"))
class SIMPLECOMBAT_API UAnimNotify_PlayAnimMontage : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotify_PlayAnimMontage();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,const FAnimNotifyEventReference& EventReference) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	FName SlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	float PlayRate;
};
