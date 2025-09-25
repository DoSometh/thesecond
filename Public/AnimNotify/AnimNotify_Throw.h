//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_Throw.generated.h"


UCLASS(meta = (DisplayName = "Throw Character"))
class SIMPLECOMBAT_API UAnimNotify_Throw : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_Throw();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	float ImpulseValue;

	//次级模型名字
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throw")
	FName SubMeshTagName;
};